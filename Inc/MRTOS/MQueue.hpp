/*
 * MQueue.hpp
 *
 *  Created on: Jun 4, 2020
 *      Author: Ali AlSaibie
 *      Email:  ali.alsaibie@ku.edu.kw
 */

#ifndef MQUEUE_HPP_
#define MQUEUE_HPP_


#include <vector>
#include "FreeRTOS.h"
#include "queue.h"
#include <functional>
#include "MTopics/common_types.hpp"
#include "stm32f4xx_hal.h"

namespace MRTOS {

typedef enum {
  Receive = 0,
  Peek
} MQReadMode;

typedef struct {
  QueueHandle_t handle = NULL;
  const char *name;
  uint32_t length;
} MQueueHandle_t;

class MQueueBase {
 public:
  inline const char* get_name() {
    return mqh.name;
  }

  inline QueueHandle_t get_handle() {
    return mqh.handle;
  }

  static std::vector<MQueueHandle_t*> ptrMQH;

 protected:
  MQueueBase(MQueueHandle_t &qh, size_t msg_size) :
      mqh(qh) {
    if (mqh.handle == NULL) {
      /* Create Queue if not created */
      mqh.handle = xQueueCreate(mqh.length, msg_size);
      ptrMQH.push_back(&mqh);
    }
  }

  MQueueHandle_t &mqh;
};

template<typename MQueuemsgT> /* Queue Data Type */
class MQueuePublisher : public MQueueBase {
 public:
  MQueuePublisher(MQueueHandle_t &qh) :
      MQueueBase(qh, sizeof(MQueuemsgT)) {
  }

  inline uint32_t publish(MQueuemsgT &msg) {
//        if (xQueueSendToBack(mqh.handle, &msg, (TickType_t)2) == pdTRUE) {
    MTopics::_msgCore *msgCore = static_cast<MTopics::_msgCore*>(&msg);
    msgCore->msg_count++;
    msgCore->tick_stamp = HAL_GetTick();
    if (xQueueOverwrite(mqh.handle, &msg) == pdTRUE) {  // TODO: create a seperate multi-publisher object
      /* Save a copy for peeking */
      return pdPASS;
    } else {
      return pdFAIL;
    }
  }

 private:
  MQueuemsgT msg;
};

template<typename MQueuemsgT>
class MQueueSubscriber : public MQueueBase {
  typedef std::function<void(const MQueuemsgT&)> callbackT;
 public:
  MQueueSubscriber(MQueueHandle_t &qh, callbackT cb_) :
      MQueueBase(qh, sizeof(MQueuemsgT)),
      cb(cb_),
      previous_tick_stamp(0),
      previous_msg_count(0) {
  }

  inline uint32_t peek() {
    if (xQueuePeek(mqh.handle, &msg, (TickType_t) 10) == pdPASS) {
      cb(msg);
      return pdPASS;
    } else {
      return pdFAIL;
    }
  }

  inline uint32_t receive() {
    if (xQueuePeek(mqh.handle, &msg, (TickType_t) 10) == pdPASS) {
      MTopics::_msgCore *msgCore = static_cast<MTopics::_msgCore*>(&msg);
      previous_tick_stamp = msgCore->tick_stamp;
      if (msgCore->msg_count > previous_msg_count) {
        previous_msg_count = msgCore->msg_count;
        cb(msg);
        return pdPASS;
      } else {
        return pdFAIL;
      }
    } else {
      return pdFAIL;
    }
  }

 private:
  MQueuemsgT msg;
  callbackT cb;
  uint32_t previous_tick_stamp;
  uint32_t previous_msg_count;
};

template<typename MQueuemsgT>
class MQueueSubscriberDep : public MQueueBase {
  typedef void (*callbackT)(const MQueuemsgT&);

 public:
  MQueueSubscriberDep(MQueueHandle_t &qh, callbackT cb_, MQReadMode mode) :
      MQueueBase(qh, sizeof(MQueuemsgT)),
      cb(cb_),
      read_mode(mode),
      previous_tick_stamp(0),
      previous_msg_count(0) {
  }

  inline uint32_t receive() {
    if (read_mode == Receive) {
      if (xQueueReceive(mqh.handle, &msg, (TickType_t) 10) == pdPASS) {
        cb(msg);
        return pdPASS;
      } else {
        return pdFAIL;
      }
    } else if (read_mode == Peek) {
      if (xQueuePeek(mqh.handle, &msg, (TickType_t) 10) == pdPASS) {
        cb(msg);
        return pdPASS;
      } else {
        return pdFAIL;
      }
    } else {
      return pdFAIL;
    }
  }

 private:
  MQueuemsgT msg;
  callbackT cb;
  MQReadMode read_mode;
  uint32_t previous_tick_stamp;
  uint32_t previous_msg_count;
};

}  // namespace MRTOS


#endif /* MQUEUE_HPP_ */
