/*
 * sensor_status.hpp
 *
 *  Created on: Jun 4, 2020
 *      Author: Ali AlSaibie
 *      Email:  ali.a@ku.edu.kw
 */

#ifndef SENSOR_STATUS_HPP_
#define SENSOR_STATUS_HPP_
#include "MRTOS/MQueue.hpp"

namespace MTopics {

typedef struct : public _msgCore {
  float Q_SLPM { 0 };
  float P_mmH2O { 0 };
} SensorStatus_msg_t;

}  // namespace MTopics

extern MRTOS::MQueueHandle_t gSensorStatusMQHandle;


#endif /* SENSOR_STATUS_HPP_ */
