/*
 * safety.hpp
 *
 *  Created on: Jun 4, 2020
 *      Author: Ali AlSaibie
 *      Email:  ali.a@ku.edu.kw
 */

#ifndef SAFETY_HPP_
#define SAFETY_HPP_

#include "MRTOS/MQueue.hpp"

namespace MTopics {
enum class SystemWarnings_Modes {
  No_Warning = 0x0,
  Soft_Limit_Hit_END1 = 0x1,
  Soft_Limit_Hit_END2 = 0x2,
  Hard_Limit_Hit_END1 = 0x4,
  Hard_Limit_Hit_END2 = 0x8,
};

enum class SystemErrors_Modes {
  No_Error = 0x0,
  Actuator_Error = 0x1,
  Sensor_Error = 0x2,
  UI_Error = 0x4
};

typedef struct : public _msgCore {
  bool warning_detected { false };
  SystemWarnings_Modes system_warning { SystemWarnings_Modes::No_Warning };
  bool error_detected { false };
  SystemErrors_Modes system_error { SystemErrors_Modes::No_Error };
  bool open_limit_reached { false };
} Safety_msg_t;

}  // namespace MTopics

extern MRTOS::MQueueHandle_t gSafetyMQHandle;



#endif /* SAFETY_HPP_ */
