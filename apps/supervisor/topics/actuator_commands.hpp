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
 * File: actuator_commands.hpp
 * Project: Crane Supervisor
 * Author: Ali AlSaibie (ali.alsaibie@ku.edu.kw)
 * -----
 * Modified By: Ali AlSaibie (ali.alsaibie@ku.edu.kw>)
 */
#ifndef ACTUATOR_COMMANDS_HPP_
#define ACTUATOR_COMMANDS_HPP_
#include "MRXTopic.hpp"
#include "actuator_common.hpp"

namespace MachineRFX {

typedef struct : public _msgCore {
    struct LinearAxis_ {
        float position{0};
        float velocity{0};
        float torque{0};
        AxisTrajectory_t trajectory;
        ActuatorModes_t mode{ActuatorModes_t::Position};
    } trolleyAxis;

} ActuatorCommands_msg_t;

inline MRXTopicHandle_t gActuatorCommandsMTHandle{"Actuator Commands"};
}  // namespace MachineRFX

#endif /* ACTUATOR_COMMANDS_HPP_ */
