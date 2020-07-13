/*
 * ODriveInterface.cpp
 *
 *  Created on: Jun 4, 2020
 *      Author: Ali AlSaibie
 *      Email:  ali.a@ku.edu.kw
 */

#include "actuators/ODrive/ODriveInterface.hpp"
#include "Device/UART.hpp"
#include <cstdio>

#include "FreeRTOS.h"
#include "task.h"

using namespace ODrive;


std::string charToString(char *arr, size_t len) {
  std::string s(arr);
  return s;
}

ODriveInterface::ODriveInterface(UART_HandleTypeDef &_huart, LinearAxis_Config_t &_config)
    :
    uart(_huart),
    config(_config) {
}

void ODriveInterface::start(uint8_t motor_number) {

  uart.start();

  uart.spin_circular();

  uint8_t start_try = 0;
  AxisErrors_t trolleyAxisError = AxisErrors_t::ERROR_NOT_RETREIVED;

  do {
    trolleyAxisError = getErrorState(motor_number);
    if (trolleyAxisError != AxisErrors_t::ERROR_NONE) {
      reboot(); /* IMPORTANT: This assumes pre-calibration is enabled on ODrive */
      vTaskDelay(10000);
    }
  } while (start_try++ < 1 && trolleyAxisError != AxisErrors_t::ERROR_NONE);

  setParameter(motor_number, AxisParameters_t::Max_Velocity, config.axis_max_vel);
  setParameter(motor_number, AxisParameters_t::Max_Current, config.axis_max_current);

}

void ODriveInterface::reboot() {
  uart.print("sr\n");
}

void ODriveInterface::eraseConfiguration() {
  uart.print("se\n");
}

void ODriveInterface::saveConfiguration() {
  uart.print("ss\n");
}

void ODriveInterface::setParameter(uint8_t motor_number, AxisParameters_t param, float value) {
  char buf_[45] { 0 };
  switch (param) {
    case AxisParameters_t::Max_Velocity:
      sprintf(buf_, "w axis%d.controller.config.vel_limit %0.2f\n", motor_number, value);
      uart.print(buf_);
      break;
    case AxisParameters_t::Max_Current:
      sprintf(buf_, "w axis%d.motor.config.current_lim %0.2f\n", motor_number, value);
      uart.print(buf_);
      break;
    default:
      break;
  }

}

void ODriveInterface::calibrateAndConfigure() {

}

uint8_t ODriveInterface::sendAxisStateCommand(uint8_t motor_number, AxisStates_t cmd, bool wait) {
  char buf_[30] { 0 };
  sprintf(buf_, "w axis%d.requested_state %d\n", motor_number, (int) cmd);
  uart.print(buf_);
  if (wait) {
    AxisStates_t state = getAxisState(motor_number);
    if (state == cmd) {
      return 1;
    } else {
      return 0;
    }
  }
}

void ODriveInterface::sendControlModeCommand(uint8_t motor_number, ClosedLoopControlModes_t cmd) {
  char buf_[55] { 0 };
  sprintf(buf_, "w axis%d.controller.config.control_mode %d\n", motor_number, (int) cmd);
  uart.print(buf_);
}

void ODriveInterface::sendPositionSp(uint8_t motor_number, float p_sp) {
  char buf_[30] { 0 };
  float sp = p_sp * config.axis_gear_ratio;

  //TODO: check we don't exceed max soft limits
  sprintf(buf_, "p %d %0.2f 0 0\n", motor_number, sp);
  uart.print(buf_);
}

void ODriveInterface::sendVelocitySp(uint8_t motor_number, float v_sp) {
  char buf_[30] { 0 };
  float sp = v_sp * config.axis_gear_ratio;

  sprintf(buf_, "v %d %0.2f 0\n", motor_number, sp);
  uart.print(buf_);
}

void ODriveInterface::sendTorqueSp(uint8_t motor_number, float tau_sp) {
  char buf_[30] { 0 };
  float sp = tau_sp / config.axis_torque_constant;
  sprintf(buf_, "c %d %0.2f\n", motor_number, sp);
  uart.print(buf_);
}

MotionState_t ODriveInterface::getMotionState(uint8_t motor_number) {

  uint32_t time_start = HAL_GetTick();
  MotionState_t state;
  /* Get position & velocity
   * Request two values at once, should receive two ascii lines as a reply */
  char buf_[90] { 0 };
  sprintf(buf_, "r axis%d.encoder.pos_estimate\nr axis%d.encoder.vel_estimate\n", motor_number, motor_number);
  uart.print(buf_);
  static const uint16_t timeout = 50;
  uint32_t timeout_start = HAL_GetTick();
  do {
    vTaskDelay(2);
    uart.spin_circular();
    if (HAL_GetTick() - timeout_start >= timeout) {
      break;
    }
  } while (uart.lines_available() < 2);
  if (uart.lines_available() > 1) {
    state.position = atof(&(uart.get_line().buf[0])) / config.axis_gear_ratio;
    state.velocity = atof(&(uart.get_line().buf[0])) / config.axis_gear_ratio;
    state.data_latency_ms = HAL_GetTick() - time_start;
  }

  /* Get velocity */
  return state;  // TODO: do something else if no data

}

AxisStates_t ODriveInterface::getAxisState(uint8_t motor_number) {
//TODO: check to see if in closed_loop mode
  static const uint16_t timeout = 50;
  char buf_[35] { 0 };
  sprintf(buf_, "r axis%d.current_state\n", motor_number);
//  clear_stream(inc_stream);
  uart.print(buf_);
  uint32_t timeout_start = HAL_GetTick();
  do {
    vTaskDelay(2);
    uart.spin_circular();
    if (HAL_GetTick() - timeout_start >= timeout) {
      break;
    }
  } while (uart.lines_available()  == 0);
  if (uart.lines_available()  != 0) {
    return static_cast<AxisStates_t>(atoi(&(uart.get_line().buf[0])));
  } else {
    return AxisStates_t::Undefined;
  }
}

AxisErrors_t ODriveInterface::getErrorState(uint8_t motor_number) {
  static const uint16_t timeout = 50;
  char buf_[35] { 0 };
  sprintf(buf_, "r axis%d.error\n", motor_number);
//  clear_stream(inc_stream);
  uart.print(buf_);
  uint32_t timeout_start = HAL_GetTick();
  do {
    vTaskDelay(2);
    uart.spin_circular();
    if (HAL_GetTick() - timeout_start >= timeout) {
      break;
    }
  } while (uart.lines_available()  == 0);
  if (uart.lines_available()  != 0) {
    return static_cast<AxisErrors_t>(atol(&(uart.get_line().buf[0])));
  } else {
    return AxisErrors_t::ERROR_NOT_RETREIVED;
  }
}

//TODO: Add interrupt on receiving new characters, and w
