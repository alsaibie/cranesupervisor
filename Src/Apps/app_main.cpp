/*
 * CraneSupervisor.cpp
 *
 *  Created on: Jun 4, 2020
 *      Author: Ali AlSaibie
 *      Email:  ali.a@ku.edu.kw
 */

#include "app_main.hpp"
#include "MRTOS/MRTOS.hpp"

#include "MTopics/actuator_commands.hpp"
#include "MTopics/operation_status.hpp"
#include "MTopics/safety.hpp"
#include "MTopics/sensor_status.hpp"
#include "MTopics/system_status.hpp"
#include "MTopics/user_input.hpp"
#include "MTopics/user_input_offboard.hpp"

std::vector<MRTOS::MQueueHandle_t *> MRTOS::MQueueBase::ptrMQH;

/* Instantiate MQHandles */
MRTOS::MQueueHandle_t gOperationStatusMQHandle{NULL, "Operation Status", 1};
MRTOS::MQueueHandle_t gSafetyMQHandle{NULL, "Safety", 1};
MRTOS::MQueueHandle_t gSensorStatusMQHandle{NULL, "Sensor Readings", 1};
MRTOS::MQueueHandle_t gActuatorCommandsMQHandle{NULL, "Actuator Commands", 1};
MRTOS::MQueueHandle_t gActuatorStatusMQHandle{NULL, "Actuator Status", 1};
MRTOS::MQueueHandle_t gSystemStatusMQHandle{NULL, "System Status", 1};
MRTOS::MQueueHandle_t gUserInputMQHandle{NULL, "User Input", 1};
MRTOS::MQueueHandle_t gUserInputOffboardMQHandle{NULL, "User Input Offboard", 1};

void appMain(void)
{

    /* Start Threads */
    /* Tasks with static allocation first */
    start_ros_manager();
    // start_pc_comms_manager();
    // start_master_manager();
    // start_safety_manager();
    // start_controller_manager();
    // start_sensor_manager();
    // start_ui_manager();
    // start_actuator_manager();
    // start_system_monitor();
}
