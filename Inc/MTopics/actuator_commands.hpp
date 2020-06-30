/*
 * actuator_commands.hpp
 *
 *  Created on: Jun 4, 2020
 *      Author: Ali AlSaibie
 *      Email:  ali.a@ku.edu.kw
 */

#ifndef ACTUATOR_COMMANDS_HPP_
#define ACTUATOR_COMMANDS_HPP_
#include "MRTOS/MQueue.hpp"
#include "common_types.hpp"

namespace MTopics {

typedef struct : public _msgCore {

    struct LinearAxis_ {
        float position{0};
        float velocity{0};
        float torque{0};
        Actuators::AxisTrajectory_t trajectory;
        Actuators::ActuatorModes_t mode{Actuators::ActuatorModes_t::Position};
    } trolleyAxis;

} ActuatorCommands_msg_t;

}  // namespace MTopics

extern MRTOS::MQueueHandle_t gActuatorCommandsMQHandle;



#endif /* ACTUATOR_COMMANDS_HPP_ */
