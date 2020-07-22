#include <cstdio>

#include "app_starter.hpp"
#include "main.h"

extern "C" {
#include "rosidl_generator_c/string_functions.h"
#include <cranesupervisor/msg/actuator_cmd.h>
#include <cranesupervisor/msg/actuator_state.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "allocators.h"
#include "task.h"
#include <rclc/executor.h>
#include <rmw_uros/options.h>
}

// these data structures for the publisher and subscriber are global, so that
// they can be configured in main() and can be used in the corresponding callback.
rcl_publisher_t my_pub;

cranesupervisor__msg__ActuatorState actuator_state_msg;
cranesupervisor__msg__ActuatorCmd actuator_cmd_msg;

void my_subscriber_callback(const void *msgin) {
    const cranesupervisor__msg__ActuatorCmd *msg = (const cranesupervisor__msg__ActuatorCmd *)msgin;
    if (msg == NULL) {
        printf("Callback: msg NULL\n");
    } else {
        printf("Callback: I heard: %d\n", msg->control_mode);
    }
}

void my_timer_callback(rcl_timer_t *timer, int64_t last_call_time) {
    rcl_ret_t rc;
    UNUSED(last_call_time);
    if (timer != NULL) {
        //printf("Timer: time since last call %d\n", (int) last_call_time);
        rc = rcl_publish(&my_pub, &actuator_state_msg, NULL);
        if (rc == RCL_RET_OK) {
            // printf("Published message %s\n", actuator_state_msg.position);
        } else {
            // printf("timer_callback: Error publishing message %s\n", actuator_state_msg.position);
        }
    } else {
        printf("timer_callback Error: timer parameter is NULL\n");
    }
}

void rclc_example(void *) {
    rcl_allocator_t freeRTOS_allocator = rcutils_get_zero_initialized_allocator();
    freeRTOS_allocator.allocate = __freertos_allocate;
    freeRTOS_allocator.deallocate = __freertos_deallocate;
    freeRTOS_allocator.reallocate = __freertos_reallocate;
    freeRTOS_allocator.zero_allocate = __freertos_zero_allocate;

    if (!rcutils_set_default_allocator(&freeRTOS_allocator)) {
        printf("Error on default allocators (line %d)\n", __LINE__);
    }

    rcl_context_t context = rcl_get_zero_initialized_context();
    rcl_init_options_t init_options = rcl_get_zero_initialized_init_options();
    rcl_allocator_t allocator = rcl_get_default_allocator();
    rcl_ret_t rc;

    // create init_options
    rc = rcl_init_options_init(&init_options, allocator);
    if (rc != RCL_RET_OK) {
        printf("Error rcl_init_options_init.\n");

    }

    // create context
    rc = rcl_init(NULL, NULL, &init_options, &context);
    if (rc != RCL_RET_OK) {
        printf("Error in rcl_init\n");

    }

    // create rcl_node
    rcl_node_t my_node = rcl_get_zero_initialized_node();
    rcl_node_options_t node_ops = rcl_node_get_default_options();
    rc = rcl_node_init(&my_node, "node_0", "executor_examples", &context, &node_ops);
    if (rc != RCL_RET_OK) {
        printf("Error in rcl_node_init\n");
    }

    // create a publisher to publish topic 'topic_0' with type std_msg::msg::String
    // my_pub is global, so that the timer callback can access this publisher.
    const char *pub_topic = "actuatorState";
    rcl_publisher_options_t pub_options = rcl_publisher_get_default_options();
    rc = rcl_publisher_init(
        &my_pub,
        &my_node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(cranesupervisor, msg, ActuatorState),
        pub_topic,
        &pub_options);
    if (RCL_RET_OK != rc) {
        printf("Error in rcl_publisher_init %s.\n", pub_topic);
        // return -1;
    }

    // create a timer, which will call the publisher every 'period' ms in the 'my_timer_callback'
    rcl_clock_t clock;
    rc = rcl_clock_init(RCL_STEADY_TIME, &clock, &allocator);
    if (rc != RCL_RET_OK) {
        printf("Error in rcl_clock_init.\n");
        // return -1;
    }
    rcl_timer_t my_timer = rcl_get_zero_initialized_timer();
    const unsigned int timer_timeout = 1000;
    rc = rcl_timer_init(
        &my_timer,
        &clock,
        &context,
        RCL_MS_TO_NS(timer_timeout),
        my_timer_callback,
        allocator);
    if (rc != RCL_RET_OK) {
        printf("Error in rcl_timer_init.\n");
        // return -1;
    } else {
        printf("Created timer with timeout %d ms.\n", timer_timeout);
    }

    // assign message to publisher
    cranesupervisor__msg__ActuatorState__init(&actuator_state_msg);

    // create subscription
    const char *sub_topic = "actuatorCmd";
    rcl_subscription_t my_sub = rcl_get_zero_initialized_subscription();
    rcl_subscription_options_t my_subscription_options = rcl_subscription_get_default_options();

    rc = rcl_subscription_init(
        &my_sub,
        &my_node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(cranesupervisor, msg, ActuatorCmd),
        sub_topic,
        &my_subscription_options);

    if (rc != RCL_RET_OK) {
        printf("Failed to create subscriber %s.\n", sub_topic);
        // return -1;
    } else {
        printf("Created subscriber %s:\n", sub_topic);
    }

    cranesupervisor__msg__ActuatorCmd__init(&actuator_cmd_msg);
    ////////////////////////////////////////////////////////////////////////////
    // Configuration of RCL Executor
    ////////////////////////////////////////////////////////////////////////////
    rclc_executor_t executor;

    // compute total number of subsribers and timers
    unsigned int num_handles = 1 + 1;
    printf("Debug: number of DDS handles: %u\n", num_handles);
    executor = rclc_executor_get_zero_initialized_executor();
    rclc_executor_init(&executor, &context, num_handles, &allocator);

    // set timeout for rcl_wait()
    unsigned int rcl_wait_timeout = 1000;  // in ms
    rc = rclc_executor_set_timeout(&executor, RCL_MS_TO_NS(rcl_wait_timeout));
    if (rc != RCL_RET_OK) {
        printf("Error in rclc_executor_set_timeout.");
    }

    // add subscription to executor
    rc = rclc_executor_add_subscription(
        &executor, &my_sub, &actuator_cmd_msg, &my_subscriber_callback,
        ON_NEW_DATA);
    if (rc != RCL_RET_OK) {
        printf("Error in rclc_executor_add_subscription. \n");
    }

    rclc_executor_add_timer(&executor, &my_timer);
    if (rc != RCL_RET_OK) {
        printf("Error in rclc_executor_add_timer.\n");
    }

    printf("Starting Executor\n");
    while (1) {
        // timeout specified in ns (here 1s)
        rclc_executor_spin_some(&executor, 1000 * (1000 * 1000));
    }

    // clean up
    rc = rclc_executor_fini(&executor);
    rc += rcl_publisher_fini(&my_pub, &my_node);
    rc += rcl_timer_fini(&my_timer);
    rc += rcl_subscription_fini(&my_sub, &my_node);
    rc += rcl_node_fini(&my_node);
    rc += rcl_init_options_fini(&init_options);
    cranesupervisor__msg__ActuatorState__fini(&actuator_state_msg);
    cranesupervisor__msg__ActuatorCmd__fini(&actuator_cmd_msg);

    if (rc != RCL_RET_OK) {
        printf("Error while cleaning up!\n");
        // return -1;
    }
    // return 0;
}

int start_rclc_example() {
    TaskHandle_t xHandle = NULL;

    /* Create the task, storing the handle. */
    BaseType_t xReturned;
    xReturned = xTaskCreate(
        rclc_example,   /* Function that implements the task. */
        "rclc example", /* Text name for the task. */
        4000,           /* Stack size in words, not bytes. */
        (void *)1,      /* Parameter passed into the task. */
        24,             /* Priority at which the task is created. */
        &xHandle);      /* Used to pass out the created task's handle. */
}