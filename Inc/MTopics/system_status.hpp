/*
 * system_status.hpp
 *
 *  Created on: Jun 4, 2020
 *      Author: Ali AlSaibie
 *      Email:  ali.a@ku.edu.kw
 */

#ifndef SYSTEM_STATUS_HPP_
#define SYSTEM_STATUS_HPP_

#include "MRTOS/MQueue.hpp"

namespace MTopics {

typedef struct : public _msgCore {
  struct {
    float exp;
    float average;
    float max;
    float min;
  } P { 0 };

  struct {
    float slpm;

  } Q { 0 };

  struct {
    float max;
    float min;
    float average;
  } V { 0 };

  struct {
    uint32_t uptime { 0 };
  } system;

} SystemStatus_msg_t;

}  // namespace MTopics

extern MRTOS::MQueueHandle_t gSystemStatusMQHandle;



#endif /* SYSTEM_STATUS_HPP_ */
