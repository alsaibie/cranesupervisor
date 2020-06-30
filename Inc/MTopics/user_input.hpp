/*
 * user_input.hpp
 *
 *  Created on: Jun 4, 2020
 *      Author: Ali AlSaibie
 *      Email:  ali.a@ku.edu.kw
 */

#ifndef USER_INPUT_HPP_
#define USER_INPUT_HPP_

#include "MRTOS/MQueue.hpp"
#include "MTopics/common_types.hpp"
#include "MTopics/user_input_offboard.hpp"

/*
 *
 */

namespace MTopics {

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
  UI::UserSystemModes_t system_mode { UI::UserSystemModes_t::Manual_Mode };
} UserInput_msg_t;

}  // namespace MTopics

extern MRTOS::MQueueHandle_t gUserInputMQHandle;

#endif /* USER_INPUT_HPP_ */
