/*
 * user_input_offboard.hpp
 *
 *  Created on: Jun 4, 2020
 *      Author: Ali AlSaibie
 *      Email:  ali.a@ku.edu.kw
 */

#ifndef USER_INPUT_OFFBOARD_HPP_
#define USER_INPUT_OFFBOARD_HPP_


#include "MRTOS/MQueue.hpp"
#include "MTopics/common_types.hpp"
/*
 *
 */
namespace MTopics {

typedef struct : public _msgCore{
  uint32_t rate_sp_hz { 0 };
  float flow_sp_lpm { 0 };
  uint32_t IE_ratio { 0 };
  uint32_t pos_sp_test { 0 };
  bool Pause{false};
  bool ESTOP{false};
  bool MotionCalibrate{false};
  UI::UserSystemModes_t system_mode { UI::UserSystemModes_t::Manual_Mode };

  void clear(){
    /* Clear non-presistent values */
    Pause = false;
    ESTOP = false;
    MotionCalibrate = false;
  }
} UserInputOffboard_msg_t;

}  // namespace MTopics

extern MRTOS::MQueueHandle_t gUserInputOffboardMQHandle;


#endif /* USER_INPUT_OFFBOARD_HPP_ */
