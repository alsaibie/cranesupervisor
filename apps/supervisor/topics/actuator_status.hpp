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
 * File: actuator_status.hpp
 * Project: Crane Supervisor
 * Author: Ali AlSaibie (ali.alsaibie@ku.edu.kw)
 * -----
 * Modified By: Ali AlSaibie (ali.alsaibie@ku.edu.kw>)
 */

#ifndef ACTUATOR_STATUS_HPP_
#define ACTUATOR_STATUS_HPP_
#include "MRXTopic.hpp"
#include "actuator_common.hpp"

namespace MachineRFX {

enum class ActuatorError_t {
  Error_None = 0,
  Error_Invalid_State = 1,
  Error_Voltage = 2,
  Error_Motor = 3,
  Error_Encoder = 4,
  Error_Controller = 5,
  Error_Watchdog
};

typedef struct : public _msgCore {

    struct LinearAxis_ {
        float position{0};
        float velocity{0};
        float current{0};
        ActuatorModes_t mode{ActuatorModes_t::Position};
        ActuatorError_t error{ActuatorError_t::Error_None};
    } trolleyAxis;

} ActuatorStatus_msg_t;

inline MRXTopicHandle_t gActuatorStatusMTHandle{"Actuator Status"};

}  // namespace MachineRFX

#endif /* ACTUATOR_STATUS_HPP_ */
