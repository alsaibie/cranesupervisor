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
 * File: user_input.hpp
 * Project: Crane Supervisor
 * Author: Ali AlSaibie (ali.alsaibie@ku.edu.kw)
 * -----
 * Modified By: Ali AlSaibie (ali.alsaibie@ku.edu.kw>)
 */

#ifndef USER_INPUT_HPP_
#define USER_INPUT_HPP_

#include "MRXTopic.hpp"
#include "ui_common.hpp"

namespace MachineRFX {

enum class ModeBtn_Modes {
  btnMODE1 = 0,
  btnMODE2,
  btnMODE3,
  btnMODE4,
  NUM_OF_BTNMODES
// TODO: Rename the modes to something meaningful
};

typedef struct : public _msgCore{
  uint32_t rate_sp_hz { 0 };
  uint32_t flow_sp_lpm { 0 };
  uint32_t IE_ratio { 0 };
  ModeBtn_Modes btn1_state { ModeBtn_Modes::btnMODE1 };
  UserSystemModes_t system_mode { UserSystemModes_t::Manual_Mode };
} UserInput_msg_t;

inline MRXTopicHandle_t  gUserInputMTHandle{"User Input"};
}  // namespace MachineRFX

#endif /* USER_INPUT_HPP_ */
