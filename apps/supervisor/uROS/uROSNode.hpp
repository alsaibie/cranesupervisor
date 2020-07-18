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
 * File: uROS.hpp
 * 
 * A convenience class for using some of ros2's rcl interface functions
 * 
 * Project: Crane Supervisor
 * Author: Ali AlSaibie (ali.alsaibie@ku.edu.kw)
 * -----
 * Modified By: Ali AlSaibie (ali.alsaibie@ku.edu.kw>)
 */

#ifndef _UROS_HPP_
#define _UROS_HPP_

extern "C" {
#include <rcl/error_handling.h>
#include <rcl/rcl.h>
#include <rcl_action/rcl_action.h>
}

class uROSNode {
   public:
    uROSNode(const char *node_name_, uint32_t dev_id_) : dev_id(dev_id_) {
        name = node_name_;
        uint32_t rc = 0;
        options = rcl_get_zero_initialized_init_options();
        context = rcl_get_zero_initialized_context();
        node_ops = rcl_node_get_default_options();
    }
    virtual ~uROSNode() {}

    inline uint32_t connect() { /* A blocking call - keep retrying to connect */
        uint32_t rc = 0;
        rc = rcl_init_options_init(&options, rcl_get_default_allocator());
        do {
            /* A successful rcl_init ensures connection to agent */
            rc = rcl_init(0, NULL, &options, &context);
            if (rc != 0) {
                printf("Connection Timeout, Retrying\n");
            }
        } while (rc != 0);

        rc = rcl_node_init(&node_handle, name, "", &context, &node_ops);

        return rc;
    }

    rcl_node_t node_handle{0};

   private:
    const char *name;
    uint32_t dev_id{0};
    rcl_init_options_t options;
    rcl_context_t context;
    rcl_node_options_t node_ops;
};

#endif  // _UROS_HPP_