/*
 * ODriveInterface.hpp
 *
 *  Created on: Jun 4, 2020
 *      Author: Ali AlSaibie
 *      Email:  ali.a@ku.edu.kw
 */

#ifndef ACTUATORS_ODRIVEINTERFACE_HPP_
#define ACTUATORS_ODRIVEINTERFACE_HPP_

#include "Device/UART.hpp"

namespace ODrive {

class ODriveUART : public UART {
 public:
  ODriveUART(UART_HandleTypeDef &handle)
      :
      UART(handle) {
  }

  virtual void process_line(const uint8_t *buf, size_t len) {
    StreamBuffer &strm = rx_sbuffer_queue[sbuffer_queue_write_idx];

    for (size_t k = 0; k < len; k++) {
      strm.buf[k] = (char) buf[k];
      //Need to copy so original is cleared immediately
    }

    strm.len = len;
    sbuffer_queue_write_idx++;
    lines_unread++;
    if (sbuffer_queue_write_idx == RX_SBUFFER_QUEUE_LENGTH) {
      sbuffer_queue_write_idx = 0;
    }

    if (lines_unread == RX_SBUFFER_QUEUE_LENGTH) {
      /* Buffer full */
    }
  }

  inline uint8_t lines_available() {
    return lines_unread;
  }

  inline StreamBuffer get_line() {
    StreamBuffer ret;
    if (lines_unread > 0) {
      ret = rx_sbuffer_queue[sbuffer_queue_read_idx];
      sbuffer_queue_read_idx++;
      if (sbuffer_queue_read_idx == RX_SBUFFER_QUEUE_LENGTH) {
        sbuffer_queue_read_idx = 0;
      }
      lines_unread--;
    }

    return ret;
  }

  inline void reset_rx_queue() {
//    for(uint8_t idx = 0; idx < ODRIVE_RX_BUFFER_LENGTH; idx++){
//      clear_stream(stream_buf);
//
//    }
  }

  inline static uint8_t const RX_SBUFFER_QUEUE_LENGTH = 10;
  StreamBuffer rx_sbuffer_queue[RX_SBUFFER_QUEUE_LENGTH] { 0 };
  uint8_t lines_unread { 0 };
  uint8_t sbuffer_queue_write_idx { 0 };
  uint8_t sbuffer_queue_read_idx { 0 };
  bool buffer_full { false };

};

typedef struct {
  int32_t axis_min_pos { 0 };  // [mm]
  int32_t axis_max_pos { 0 };  // [mm]
  int32_t axis_max_vel { 0 };  // [mm/s]
  float axis_gear_ratio { 0 };  //
  float axis_torque_constant { 0 };  //
  int32_t axis_max_acc { 0 };  // [mm/s]
  int32_t axis_max_current { 0 };  // [A]
  int32_t soft_limit_tolerance { 0 };  // [mm]
} LinearAxis_Config_t;

typedef struct {
  float position { 0 };
  float velocity { 0 };
  float acceleration { 0 };
  float current { 0 };
  uint32_t data_latency_ms;
} MotionState_t;

typedef struct {
  int e { 0 };
} ErrorState_t;

enum class AxisParameters_t {
  Max_Current = 0,
  Max_Velocity = 1,
  Max_Acceleration = 2,
};

enum class MotionStates_t {
  Position = 0,
  Velocity = 1
//  Current = 2
};

enum class ClosedLoopControlModes_t {
  Position = 0,
  Velocity = 1,
  Current = 2,
  Voltage = 3
};

enum class AxisStates_t {
  Undefined = 0,
  Idle = 1,
  Startup_Sequence = 2,
  Full_Calibration_Sequence = 3,
  Motor_Calibration = 4,
  Sensorless_Control = 5,
  Encoder_Index_Search = 6,
  Encoder_Offset_Calibration = 7,
  Closed_Loop_Control = 8
};

enum class AxisErrors_t {
  ERROR_NONE = 0x00,
  ERROR_INVALID_STATE = 0x01,  //<! an invalid state was requested
  ERROR_DC_BUS_UNDER_VOLTAGE = 0x02,
  ERROR_DC_BUS_OVER_VOLTAGE = 0x04,
  ERROR_CURRENT_MEASUREMENT_TIMEOUT = 0x08,
  ERROR_BRAKE_RESISTOR_DISARMED = 0x10,  //<! the brake resistor was unexpectedly disarmed
  ERROR_MOTOR_DISARMED = 0x20,  //<! the motor was unexpectedly disarmed
  ERROR_MOTOR_FAILED = 0x40,  // Go to motor.hpp for information, check odrvX.axisX.motor.error for error value
  ERROR_SENSORLESS_ESTIMATOR_FAILED = 0x80,
  ERROR_ENCODER_FAILED = 0x100,  // Go to encoder.hpp for information, check odrvX.axisX.encoder.error for error value
  ERROR_CONTROLLER_FAILED = 0x200,
  ERROR_POS_CTRL_DURING_SENSORLESS = 0x400,
  ERROR_WATCHDOG_TIMER_EXPIRED = 0x800,
  ERROR_NOT_RETREIVED = 0x1000
};

class ODriveInterface {
 public:
  ODriveInterface(UART_HandleTypeDef &_huart, LinearAxis_Config_t &_config);

  ~ODriveInterface() {

  }

  void start(uint8_t motor_number);
  void reboot();
  void eraseConfiguration();
  void calibrateAndConfigure();
  void saveConfiguration();
  void spin() {
    uart.clear_rx_dma_buffer();  //TODO: verify if works
    uart.spin_circular();

  }

  void setParameter(uint8_t motor_number, AxisParameters_t param, float value);
  uint8_t sendAxisStateCommand(uint8_t motor_number, AxisStates_t cmd, bool wait);
  void sendControlModeCommand(uint8_t motor_number, ClosedLoopControlModes_t cmd);

  void sendVelocitySp(uint8_t motor_number, float v_sp);
  void sendPositionSp(uint8_t motor_number, float p_sp);
  void sendTorqueSp(uint8_t motor_number, float tau_sp);

  MotionState_t getMotionState(uint8_t motor_number);
  AxisStates_t getAxisState(uint8_t motor_number);
  AxisErrors_t getErrorState(uint8_t motor_number);

 private:
  LinearAxis_Config_t &config;
  ODriveUART uart;
//  StreamBuffer &inc_stream; /* Will hold the latest char arr line */
};

}

#endif /* ACTUATORS_ODRIVEINTERFACE_HPP_ */
