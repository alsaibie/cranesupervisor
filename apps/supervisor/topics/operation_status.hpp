/*
 * operation_status.hpp
 *
 *  Created on: Jun 4, 2020
 *      Author: Ali AlSaibie
 *      Email:  ali.a@ku.edu.kw
 */

#ifndef OPERATION_STATUS_HPP_
#define OPERATION_STATUS_HPP_

#include "MRXTopic.hpp"
#include "ui_common.hpp"

namespace MachineRFX {

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
  UserInputSource_t input_source { UserInputSource_t::Offboard };
  UserSystemModes_t operation_mode {UserSystemModes_t::Manual_Mode};
} OperationStatus_msg_t;

inline MRXTopicHandle_t gOperationStatusMTHandle{"Operation Status"};

}  // namespace MachineRFX





#endif /* OPERATION_STATUS_HPP_ */
