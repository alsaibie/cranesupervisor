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
 * A convenience class for using some of ros2's rclc interface functions
 *
 * Project: Crane Supervisor
 * Author: Ali AlSaibie (ali.alsaibie@ku.edu.kw)
 * -----
 * Modified By: Ali AlSaibie (ali.alsaibie@ku.edu.kw>)
 */

#ifndef _UROS_HPP_
#define _UROS_HPP_

extern "C" {
#include <rclc/executor.h>
#include <rclc/rclc.h>
#include <rmw_uros/options.h>
}

#include <functional>

class uROSNode
{
public:
  uROSNode(const char * node_name_, const char * node_namespace_, uint32_t dev_id_)
  : dev_id(dev_id_)
  {
    this->node_name = node_name_;
    this->node_namespace = node_namespace_;
    this->init_options = rcl_get_zero_initialized_init_options();
    this->context = rcl_get_zero_initialized_context();
    this->node_handle = rcl_get_zero_initialized_node();
    this->node_options = rcl_node_get_default_options();
    this->executor = rclc_executor_get_zero_initialized_executor();
  }
  virtual ~uROSNode() {}

  inline uint32_t connect()     /* A blocking call - keep retrying to connect */
  {
    rcl_ret_t rc = 0;
    this->allocator = rcl_get_default_allocator();

    /* Create init options */
    rc = rcl_init_options_init(&init_options, allocator);
    if (rc != RCL_RET_OK) {
      printf("Error rcl_init_options_init\n");
    }

    // create context
    rc = rcl_init(NULL, NULL, &init_options, &context);
    if (rc != RCL_RET_OK) {
      printf("Error in rcl_init.\n");
    }
    
    do {
      /* A successful rcl_node_init ensures connection to agent */
      rc = rcl_node_init(&node_handle, node_name, node_namespace, &context, &node_options);
      if (rc != RCL_RET_OK) {
        printf("Error in rclc_node_init_default\n");
      }
    } while (rc != 0);

    return rc;
  }

  inline uint32_t start_executor(uint32_t num_handles_)      // TODO: move num handles to base
  {
    rcl_ret_t rc = 0;
    num_handles = num_handles_;
    rc = rclc_executor_init(&executor, &context, num_handles, &allocator);
    // set timeout for rcl_wait()
    unsigned int rcl_wait_timeout = 100;      // in ms
    rc = rclc_executor_set_timeout(&executor, RCL_MS_TO_NS(rcl_wait_timeout));
    if (rc != RCL_RET_OK) {
      printf("Error in rclc_executor_set_timeout\n");
    }
  }
  inline uint32_t spin_once(uint32_t dt)
  {
    // timeout specified in ns
    rclc_executor_spin_some(&executor, RCL_MS_TO_NS(dt));
  }

  inline uint32_t add_subscription(
    rcl_subscription_t * subscription, void * msg,
    rclc_callback_t callback)
  {
    rcl_ret_t rc = 0;
    // add subscription to executor
    rc = rclc_executor_add_subscription(&this->executor, subscription, msg, callback, ON_NEW_DATA);
    if (rc != RCL_RET_OK) {
      printf("Error in rclc_executor_add_subscription\n");
    }
  }

  rcl_node_t node_handle{0};

private:
  rcl_allocator_t allocator;
  rcl_init_options_t init_options;
  rclc_support_t support;
  rclc_executor_t executor;
  const char * node_name;
  const char * node_namespace;
  uint32_t dev_id{0};
  uint32_t num_handles{0};

  rcl_context_t context;
  rcl_node_options_t node_options;
};

#endif  // _UROS_HPP_
