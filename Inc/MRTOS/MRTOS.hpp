/*
 * MRTOS.hpp
 *
 *  Created on: Jun 4, 2020
 *      Author: Ali AlSaibie
 *      Email:  ali.a@ku.edu.kw
 */

#ifndef MRTOS_HPP_
#define MRTOS_HPP_

#include "MQueue.hpp"
#include "MThread.hpp"

typedef enum {
    rtosPriorityIdle = -3,        /* idle (lowest) */
    rtosPriorityLow = -2,         /* (low) */
    rtosPriorityBelowNormal = -1, /* below normal */
    rtosPriorityNormal = 0,       /* normal (default) */
    rtosPriorityAboveNormal = +1, /* above normal */
    rtosPriorityHigh = +2,        /* high */
    rtosPriorityRealtime = +3,    /* realtime (highest) */
    rtosPriorityError = 0x84      /* system cannot determine priority or thread has illegal priority */
} RTOSPriority_T;


#endif /* MRTOS_HPP_ */
