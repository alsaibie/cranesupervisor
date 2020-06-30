/*
 * common_types.hpp
 *
 *  Created on: Jun 4, 2020
 *      Author: Ali AlSaibie
 *      Email:  ali.a@ku.edu.kw
 */

#ifndef COMMON_TYPES_HPP_
#define COMMON_TYPES_HPP_

#include <cstdint>

namespace MTopics {
struct _msgCore {
  uint32_t tick_stamp { 0 };
  uint32_t msg_count { 0 };
};

}

namespace Actuators {

/* Generic Motion Trajectory */
typedef struct {
  uint32_t *traj_arr;
  uint32_t traj_arr_length;
  uint32_t sample_time;
  bool cyclical; /* If cyclical: must be a closed path -> end = start */
} AxisTrajectory_t;

enum class ActuatorModes_t {
  Position = 0,
  Velocity,
  Torque,
  PositionTrajectory,
  VelocityTrajectory,
  TorqueTrajectory,

  Num_of_Modes
};

}  // namespace Actuators

namespace UI {
enum class UserSystemModes_t {
  Manual_Mode = 1,
  Pressure_Control,
  Pressure_Assist,
  Volume_Control,
  EndOfList
};

enum class UserInputSource_t {
  Onboard = 1,
  Offboard
};

inline UserSystemModes_t& operator++(UserSystemModes_t &m) {
  m = static_cast<UserSystemModes_t>(static_cast<int>(m) + 1);

  if (m == UserSystemModes_t::EndOfList) {
    m = UserSystemModes_t::Manual_Mode;
  }

  return m;
}

}




#endif /* COMMON_TYPES_HPP_ */
