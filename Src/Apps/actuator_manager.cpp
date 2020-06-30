/*
 * Actuator_Manager.cpp
 *
 *  Created on: Jun 4, 2020
 *      Author: Ali AlSaibie
 *      Email:  ali.a@ku.edu.kw
 */
#include "board_configuration.hpp"
#include "app_main.hpp"
#include "MTopics/actuator_commands.hpp"
#include "MTopics/actuator_status.hpp"
#include "Actuators/ODriveInterface.hpp"

#include "task.h"

#include "math.h"

using namespace MRTOS;
using namespace MTopics;
using namespace Actuators;
using namespace ODrive;

extern ODrive::ODriveInterface ODrive0;
#define odrive0_huart huart2
extern UART_HandleTypeDef odrive0_huart;

/* Declare Axis Configuration */

#define trAxisMinPos -900 // [mm]
#define trAxisMaxPos 900 // [mm]
#define trAxisMaxVel 50000 // [mm/s]
#define trAxisGearRatio 3.0f
#define trAxisTorqueK 3.0f
#define trAxisMaxAcc 2000 // [mm/s^2]
#define trAxisMaxCurrent 20 // [A]
#define trAxisSoftLimitTolerance 50 // [mm]

enum Odrive0Axes {
  TROLLEY = 0,
  BRIDGE = 1
};

class ActuatorManager : public MThread {
 public:
  ActuatorManager()
      :
      MThread("Actuator Manager ", 512, actuator_m_priority, 30),
      actuator_status_pub(gActuatorStatusMQHandle),
      actuator_cmd_sub(gActuatorCommandsMQHandle,
                       std::bind(&ActuatorManager::on_actuator_cmd_read, this, std::placeholders::_1)),
      odrive0config { trAxisMinPos, trAxisMaxPos, trAxisMaxVel, trAxisGearRatio, trAxisTorqueK,
      trAxisMaxAcc, trAxisMaxCurrent, trAxisSoftLimitTolerance },
      odrive0(odrive0_huart, odrive0config) {
  }

  virtual ~ActuatorManager() {

  }
 protected:
  virtual void run() {

//     odrive0.start(TROLLEY);

//     AxisStates_t trolleyAxisState = odrive0.getAxisState(TROLLEY);
//     uint32_t count = 0;

//     if (trolleyAxisState != AxisStates_t::Closed_Loop_Control) {
//       odrive0.sendAxisStateCommand(TROLLEY, AxisStates_t::Closed_Loop_Control, true);
//     }

    while (1) {
//       /*
//        * Upon receiving the command from the controller. Any actuator mode changes
//        * will be done, and the corresponding setpoint for each will be set.
//        * The spinAxis call is a synchronous call to command the motors directly
//        * */
//       odrive0.spin();

//       actuator_cmd_sub.receive();
//       float ptest = 9000 * sin(10*3.14 * count++ / 1000.0 );
// //      float ptest = 0;
//       switch (actuatorCmdMsg.trolleyAxis.mode) {
//         case ActuatorModes_t::Position:
// //          odrive0.sendPositionSp(TROLLEY, actuatorCmdMsg.trolleyAxis.position);
//           odrive0.sendPositionSp(TROLLEY, ptest);
//           break;
//         case ActuatorModes_t::Velocity:
//           odrive0.sendVelocitySp(TROLLEY, actuatorCmdMsg.trolleyAxis.velocity);
//           break;
//         case ActuatorModes_t::Torque:
//           break;
//         case ActuatorModes_t::PositionTrajectory:
//           break;
//         case ActuatorModes_t::VelocityTrajectory:
//           break;
//         case ActuatorModes_t::TorqueTrajectory:
//           break;
//         default:
//           break;
//       }

//       /* Check axis state at a lower rate TODO: change to 1 Hz fixed */
//       /* TODO: This breaks the RTOS of the thread, no */

//       static uint8_t axis_state_rate_check_multiplier = 0;
//       if(axis_state_rate_check_multiplier++ == 10){
//         trolleyAxisState = odrive0.getAxisState(TROLLEY);
//         axis_state_rate_check_multiplier = 0;
//       }
//       MotionState_t TrolleyMotionState = odrive0.getMotionState(TROLLEY);
//       ActuatorStatusMsg.trolleyAxis.mode = ActuatorModes_t::Position;
//       ActuatorStatusMsg.trolleyAxis.position = TrolleyMotionState.position;
//       ActuatorStatusMsg.trolleyAxis.velocity = TrolleyMotionState.velocity;
//       actuator_status_pub.publish(ActuatorStatusMsg);

//       float pos_error = ActuatorStatusMsg.trolleyAxis.position - ptest;
      //TODO: send actuator motion state
      thread_lap();
    }
  }

 private:

  void on_actuator_cmd_read(const ActuatorCommands_msg_t &msg) {
    actuatorCmdMsg = msg;
  }

  /* Pubs */
  MQueuePublisher<ActuatorStatus_msg_t> actuator_status_pub;
  ActuatorStatus_msg_t ActuatorStatusMsg;

  /* Subs */
  MQueueSubscriber<ActuatorCommands_msg_t> actuator_cmd_sub;
  ActuatorCommands_msg_t actuatorCmdMsg;
  ODrive::LinearAxis_Config_t odrive0config;
  ODrive::ODriveInterface odrive0;

};

//StreamBuffer ActuatorManager::incoming_rx_stream;

void start_actuator_manager() {
  ActuatorManager *ptr = new ActuatorManager();
  ptr->start();
}

