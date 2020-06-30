/*
 * operation_status.hpp
 *
 *  Created on: Jun 4, 2020
 *      Author: Ali AlSaibie
 *      Email:  ali.a@ku.edu.kw
 */

#ifndef OPERATION_STATUS_HPP_
#define OPERATION_STATUS_HPP_

#include "MRTOS/MQueue.hpp"
#include "MTopics/common_types.hpp"

namespace MTopics {

enum class OperationState_Modes {
  Disarmed = 0,
  Ready,
  Running,
  Running_Warning,
  Calibrating,
  Num_Operating_States
};


typedef struct : public _msgCore {
  OperationState_Modes operation_state { OperationState_Modes::Disarmed };
  UI::UserInputSource_t input_source { UI::UserInputSource_t::Offboard };
  UI::UserSystemModes_t operation_mode {UI::UserSystemModes_t::Manual_Mode};
} OperationStatus_msg_t;

}  // namespace MTopics

extern MRTOS::MQueueHandle_t gOperationStatusMQHandle;




#endif /* OPERATION_STATUS_HPP_ */
