
#include <cstdio>

#include "MachineRFX.hpp"
#include "app_starter.hpp"
#include "main.h"
#include "uROS/uROSNode.hpp"
#include "uROS/uROSTopic.hpp"

extern "C" {
#include <rcl/error_handling.h>
#include <rcl/rcl.h>
#include <rcl_action/rcl_action.h>
#include <rmw_microxrcedds_c/config.h>
#include <rmw_uros/options.h>
#include <ucdr/microcdr.h>
#include <unistd.h>
#include <uxr/client/client.h>

#include "allocators.h"
#include "rosidl_generator_c/string_functions.h"
}

#include <std_msgs/msg/header.h>

#include "cranesupervisor/msg/num.h"

#define STRING_BUFFER_LEN 100

using namespace MachineRFX;

class ROSManager : public MRXThread {
   public:
    ROSManager()
        : MRXThread("ros_manager", 3000, MRXPriority_n::Normal, 1000),
          ros_node("crane_supervisor", 0x10),
          topic_num_pub("/CraneSupervisor/Num", ros_node.node_handle, ROSIDL_GET_MSG_TYPE_SUPPORT(cranesupervisor, msg, Num)) {
    }

    virtual ~ROSManager() {
    }

   protected:
    virtual void run() {
        rcl_ret_t rc;
        //TODO: add guards on rc and perhaps a recycle goto statement. Maybe an assert macro?
        while (1) {
            rc = ros_node.connect();
            rc = topic_num_pub.initialize();
            
            numMsg.num = 0;
            bool reconnect = false;

            while (!reconnect) {
                numMsg.num++;
                topic_num_pub.publish(numMsg);
                thread_lap();
            }
        }
    }

   private:
    /* internal receives */
    void on_int_topic_receive();
    void on_int_action_response_receive();
    void on_int_service_response_receive();

    /* external receives */
    void on_ext_set_parameters_receive();
    void on_ext_action_receive();
    void on_ext_service_receive();


    /* Node */
    uROSNode ros_node;

    /* Pubs */
    uROSTopicPublisher<cranesupervisor__msg__Num> topic_num_pub;
    cranesupervisor__msg__Num numMsg;

    /* Subs */
};

void start_ros_manager(void) {
    //TODO: take this back to main.c, it is platform dependent.
    rcl_allocator_t freeRTOS_allocator = rcutils_get_zero_initialized_allocator();
    freeRTOS_allocator.allocate = __freertos_allocate;
    freeRTOS_allocator.deallocate = __freertos_deallocate;
    freeRTOS_allocator.reallocate = __freertos_reallocate;
    freeRTOS_allocator.zero_allocate = __freertos_zero_allocate;

    if (!rcutils_set_default_allocator(&freeRTOS_allocator)) {
        printf("Error on default allocators (line %d)\n", __LINE__);
    }

    ROSManager *ptr = new ROSManager();
    ptr->start();
}