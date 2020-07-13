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
 * File: safety.hpp
 * Project: Crane Supervisor
 * Author: Ali AlSaibie (ali.alsaibie@ku.edu.kw)
 * -----
 * Modified By: Ali AlSaibie (ali.alsaibie@ku.edu.kw>)
 */

#ifndef SAFETY_HPP_
#define SAFETY_HPP_

#include "MRXTopic.hpp"

namespace MachineRFX {
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

inline MRXTopicHandle_t gSafetyMTHandle{"Safety"};

}  // namespace MachineRFX





#endif /* SAFETY_HPP_ */
