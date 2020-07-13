/*
 * MThread.hpp
 *
 *  Created on: Jun 4, 2020
 *      Author: Ali AlSaibie
 *      Email:  ali.a@ku.edu.kw
 */

#ifndef MTHREAD_HPP_
#define MTHREAD_HPP_

#include "FreeRTOS.h"
#include "task.h"

namespace MRTOS {

enum class ThreadStatus_t {
  Thread_Healthy = 0x00,
  Thread_Period_Missed = 0x01,
  Thread_Duration_Overflow = 0x02,
  Thread_Sleep = 0x04
};

class MThread 
{
 public:
  inline uint32_t start() {
    // TODO: Add check guards
    if (xTaskCreate(&task, thread_name, thread_stack_depth, (void*) this, thread_priority, &task_handle) ==
    pdPASS) {
      return pdPASS;
    } else {
      return pdFAIL;
    }
  }

  inline char* get_name() {
    return pcTaskGetName(task_handle);
  }

 protected:
  MThread(const char *name, uint32_t stack_depth, uint32_t priority, uint32_t Ts_ms)
      :
      thread_stack_depth(stack_depth),
      thread_priority(priority),
      t_sampling_ticks(pdMS_TO_TICKS(Ts_ms)),
      initializedDelay(false) {
    thread_name = name;
  }
  ;
  ~MThread() {
  }

  inline static void task(void *arg) {
    MThread *ptr = static_cast<MThread*>(arg);
    ptr->run();
  }

  virtual void run() { /* Redefine this function when inheriting */
    /* Do thread stuff */
    thread_lap(); /* Call to complete the thread period */
  }

  inline void thread_lap() {
    if (!initializedDelay) {
      initializedDelay = true;
      previousWakeTick = xTaskGetTickCount();
    }
    task_excution_ticks = xTaskGetTickCount() - thread_start_ticks;
    thread_status = ThreadStatus_t::Thread_Healthy;
    if (task_excution_ticks > t_sampling_ticks) {
      thread_status = ThreadStatus_t::Thread_Duration_Overflow;
    }
    vTaskDelayUntil(&previousWakeTick, t_sampling_ticks / portTICK_PERIOD_MS);
    thread_start_ticks = xTaskGetTickCount();
  }

 private:
  const char *thread_name;

  TaskHandle_t task_handle;
  uint32_t thread_stack_depth;
  uint32_t thread_priority;
  TickType_t t_sampling_ticks;
  bool initializedDelay;
  TickType_t previousWakeTick { 0 };
  TickType_t thread_start_ticks { 0 };
  TickType_t task_excution_ticks { 0 };
  ThreadStatus_t thread_status;
};

}  // namespace MRTOS

#endif /* MTHREAD_HPP_ */
