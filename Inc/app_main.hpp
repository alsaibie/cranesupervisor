#ifndef _APP_H_
#define _APP_H_



#include "main.h"
#include "MRTOS/MRTOS.hpp"

/* Main App  - Call in main */

extern uint64_t uwTickMicroseconds;

static inline uint64_t GetTickMicroseconds(){
  return uwTickMicroseconds;
}

/* Declare Global Thread Start C-Compatible Functions - for portability */

void start_ros_manager(void);
const RTOSPriority_T ros_m_priority = rtosPriorityRealtime;

// void start_master_manager(void);
// const RTOSPriority_T master_m_priority = rtosPriorityNormal;

// void start_safety_manager(void);
// const RTOSPriority_T safety_m_priority = rtosPriorityRealtime;

// void start_controller_manager(void);
// const RTOSPriority_T controller_m_priority = rtosPriorityRealtime;

// void start_sensor_manager(void);
// const RTOSPriority_T sensor_m_priority = rtosPriorityNormal;

void start_actuator_manager(void);
const RTOSPriority_T actuator_m_priority = rtosPriorityRealtime;

// void start_ui_manager(void);
// const RTOSPriority_T ui_m_priority = rtosPriorityIdle;

// void start_emulator_manager(void);
// const RTOSPriority_T emulator_m_priority = rtosPriorityIdle;

// void start_system_monitor(void);
// const RTOSPriority_T system_mon_priority = rtosPriorityHigh;

// void start_pc_comms_manager(void);
// const RTOSPriority_T pc_comms_m_priority = rtosPriorityIdle;



/* Utility Functions */
#define DPrint(X) debug_print(X)

void debug_print(char *buf);
extern int16_t uart_debug_tx_stream_idx;

// // App main function
#ifdef __cplusplus
extern "C" {
#endif
void start_ros_interface(void);
#ifdef __cplusplus
}
#endif 

#endif // _APP_H_
