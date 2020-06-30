/*
 * actuator_status.hpp
 *
 *  Created on: Jun 4, 2020
 *      Author: Ali AlSaibie
 *      Email:  ali.a@ku.edu.kw
 */

#ifndef ACTUATOR_STATUS_HPP_
#define ACTUATOR_STATUS_HPP_
#include "MRTOS/MQueue.hpp"
#include "common_types.hpp"

namespace MTopics {

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
        Actuators::ActuatorModes_t mode{Actuators::ActuatorModes_t::Position};
        ActuatorError_t error{ActuatorError_t::Error_None};
    } trolleyAxis;

} ActuatorStatus_msg_t;

}  // namespace MTopics

extern MRTOS::MQueueHandle_t gActuatorStatusMQHandle;



#endif /* ACTUATOR_STATUS_HPP_ */
