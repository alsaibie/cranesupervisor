/*
 * MIT License
 * 
 * Copyright (c) 2020 Ali AlSaibie
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * 
 * File: actuator_manager.cpp
 * Project: Crane Supervisor
 * Author: Ali AlSaibie (ali.alsaibie@ku.edu.kw)
 * -----
 * Modified By: Ali AlSaibie (ali.alsaibie@ku.edu.kw>)
 */
#include "board_configuration.hpp"
#include "app_starter.hpp"
#include "MachineRFX.hpp"
#include "topics/actuator_commands.hpp"
#include "topics/actuator_status.hpp"
#include "actuators/ODrive/ODriveInterface.hpp"

#include "math.h"

using namespace MachineRFX;


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

class ActuatorManager : public MRXThread {
 public:
  ActuatorManager()
      :
      MRXThread("actuator_manager", 256, MRXPriority_n::Realtime, 30),
      actuator_status_pub(gActuatorStatusMTHandle),
      actuator_cmd_sub(gActuatorCommandsMTHandle,
                       std::bind(&ActuatorManager::on_actuator_cmd_read, this, std::placeholders::_1)),
      odrive0config { trAxisMinPos, trAxisMaxPos, trAxisMaxVel, trAxisGearRatio, trAxisTorqueK,
      trAxisMaxAcc, trAxisMaxCurrent, trAxisSoftLimitTolerance },
      odrive0(odrive0_huart, odrive0config) {
  }

  virtual ~ActuatorManager() {

  }
 protected:
  virtual void run() {

    /* Check if connected to odrive0 */

    

    // odrive0.start(TROLLEY);

    // AxisStates_t trolleyAxisState = odrive0.getAxisState(TROLLEY);
    // uint32_t count = 0;

    /* */

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
      toggleLD2();
    }
  }

 private:

  void on_actuator_cmd_read(const ActuatorCommands_msg_t &msg) {
    actuatorCmdMsg = msg;
  }

  /* Pubs */
  MRXTopicPublisher<ActuatorStatus_msg_t> actuator_status_pub;
  ActuatorStatus_msg_t ActuatorStatusMsg;

  /* Subs */
  MRXTopicSubscriber<ActuatorCommands_msg_t> actuator_cmd_sub;
  ActuatorCommands_msg_t actuatorCmdMsg;
  ODrive::LinearAxis_Config_t odrive0config;
  ODrive::ODriveInterface odrive0;

};

//StreamBuffer ActuatorManager::incoming_rx_stream;

void start_actuator_manager() {
  ActuatorManager *ptr = new ActuatorManager();
  ptr->start();
}

