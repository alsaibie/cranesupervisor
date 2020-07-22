/*
 * MIT License
 * 
 * Copyright (c) 2020 Ali AlSaibie
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * 
 * File: app_starter.hpp
 * Project: Crane Supervisor
 * Author: Ali AlSaibie (ali.alsaibie@ku.edu.kw)
 * -----
 * Modified By: Ali AlSaibie (ali.alsaibie@ku.edu.kw>)
 */

#ifndef _APP_STARTER_HPP_
#define _APP_STARTER_HPP_

// #include "MRXUtil.hpp"

#include <cstdint>

#ifdef __cplusplus
extern "C" {
#endif
/* App Starter  - call in main.c */
int app_starter(int argc, char **argv);
#ifdef __cplusplus
}
#endif


extern uint64_t uwTickMicroseconds;

static inline uint64_t GetTickMicroseconds(){
  return uwTickMicroseconds;
}

/* Declare Global Thread Start C-Compatible Functions - for portability */

void start_ros_manager(void);
int start_rclc_example(void);
// void start_master_manager(void);
// const RTOSPriority_T master_m_priority = rtosPriorityNormal;

// void start_safety_manager(void);
// const RTOSPriority_T safety_m_priority = rtosPriorityRealtime;

// void start_controller_manager(void);
// const RTOSPriority_T controller_m_priority = rtosPriorityRealtime;

// void start_sensor_manager(void);
// const RTOSPriority_T sensor_m_priority = rtosPriorityNormal;

void start_actuator_manager(void);

// void start_ui_manager(void);
// const RTOSPriority_T ui_m_priority = rtosPriorityIdle;

// void start_emulator_manager(void);
// const RTOSPriority_T emulator_m_priority = rtosPriorityIdle;

// void start_system_monitor(void);
// const RTOSPriority_T system_mon_priority = rtosPriorityHigh;

// void start_pc_comms_manager(void);
// const RTOSPriority_T pc_comms_m_priority = rtosPriorityIdle;



/* Utility Functions */
// #define DPrint(X) debug_print(X)

// void debug_print(char *buf);
// extern int16_t uart_debug_tx_stream_idx;


#endif // _APP_STARTER_HPP_
