
#include <cstdio>

#include "MachineRFX.hpp"
#include "app_starter.hpp"
#include "main.h"

extern "C" {
#include "allocators.h"
}

#include "cranesupervisor/msg/actuator_cmd.h"
#include "cranesupervisor/msg/actuator_state.h"
#include "uROS/uROSNode.hpp"
#include "uROS/uROSTopic.hpp"

#define STRING_BUFFER_LEN 100

using namespace MachineRFX;
using namespace std::placeholders; 
class ROSManager : public MRXThread {
   public:

    ROSManager()
        : MRXThread("ros_manager", 3000, MRXPriority_n::Normal, 1000),
          ros_node("crane_supervisor", 0x10),
          actuatorState_pub("/CraneSupervisor/ActuatorState", ros_node.node_handle, ROSIDL_GET_MSG_TYPE_SUPPORT(cranesupervisor, msg, ActuatorState)),
          actuatorCmd_sub("/CraneSupervisor/ActuatorCmd", ros_node.node_handle, ROSIDL_GET_MSG_TYPE_SUPPORT(cranesupervisor, msg, ActuatorCmd),
                          std::bind(&ROSManager::on_actuatorCmd_receive, this, _1)) {
    }

    virtual ~ROSManager() {
    }

   protected:
    virtual void run() {
        rcl_ret_t rc;
        while (1) {
            rc = ros_node.connect();
            rc = actuatorState_pub.initialize();
            rc = actuatorCmd_sub.initialize();

            actuatorStateMsg.control_mode = 0;
            bool reconnect = false;

            while (!reconnect) {
                actuatorStateMsg.control_mode++;
                actuatorState_pub.publish(actuatorStateMsg);
                actuatorCmd_sub.receive();
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
    void on_actuatorCmd_receive(const cranesupervisor__msg__ActuatorCmd &msg) {
        printf("Callback\n");
    }
    void on_ext_action_receive();
    void on_ext_service_receive();

    /* Node */
    uROSNode ros_node;

    /* Pubs */
    uROSPublisher<cranesupervisor__msg__ActuatorState> actuatorState_pub;
    cranesupervisor__msg__ActuatorState actuatorStateMsg;

    /* Subs */
    uROSSubscriber<cranesupervisor__msg__ActuatorCmd> actuatorCmd_sub;
    cranesupervisor__msg__ActuatorCmd actuatorCmdMsg;
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