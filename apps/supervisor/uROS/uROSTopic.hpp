/*
 * MIT License
 *
 * Copyright (c) 2020 Ali AlSaibie
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy
 * of this software and associated documentation files (the "Software"), to
 * deal
 * in the Software without restriction, including without limitation the
 * rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE
 * SOFTWARE.
 *
 *
 * File: uROSTopic.hpp
 * Project: Crane Supervisor
 * Author: Ali AlSaibie (ali.alsaibie@ku.edu.kw)
 * -----
 * Modified By: Ali AlSaibie (ali.alsaibie@ku.edu.kw>)
 */

#ifndef _UROSTOPIC_HPP_
#define _UROSTOPIC_HPP_

extern "C" {
#include <rcl/error_handling.h>
#include <rcl/rcl.h>

/* #include <rcl_action/rcl_action.h> */
}
#include <functional>
#include "uROSNode.hpp"

template<typename ROSTopicMsgT>
class uROSPublisher
{
public:
  uROSPublisher(
    const char * name_, const rcl_node_t & nh_,
    const rosidl_message_type_support_t * type_support_)
  : node_handle(nh_), type_support(type_support_)
  {
    topic_name = name_;
    publisher_options = rcl_publisher_get_default_options();
    publisher_options.qos.reliability = RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT;
  }
  virtual ~uROSPublisher()
  {
  }
  uint32_t initialize()
  {
    uint32_t rc = 0;

    rc = rcl_publisher_init(
      &publisher_handle, &node_handle, type_support,
      topic_name, &publisher_options);
    return rc;
  }
  uint32_t publish(ROSTopicMsgT & msg)
  {
    uint32_t rc = 0;

    rc = rcl_publish(&publisher_handle, (const void *)&msg, NULL);
    return rc;
  }
  const rcl_node_t & node_handle;

  rcl_publisher_t publisher_handle{0};
  rcl_publisher_options_t publisher_options;
  const rosidl_message_type_support_t * type_support;
  const char * topic_name;

private:
};

template<typename ROSTopicMsgT>
class uROSSubscriber
{
/* typedef std::function<void(const ROSTopicMsgT &)> callbackT; */

public:
  uROSSubscriber(
    const char * name_, uROSNode & node_,
    const rosidl_message_type_support_t * type_support_)
  : uros_node(node_), type_support(
      type_support_)
  {
    topic_name = name_;
    subscriber_options =
      rcl_subscription_get_default_options();
    subscriber_options.qos.reliability =
      RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT;
    subscriber_handle =
      rcl_get_zero_initialized_subscription();
  }
  virtual ~uROSSubscriber()
  {
  }
  uint32_t initialize(ROSTopicMsgT & msg, rclc_callback_t cb)
  {
    uint32_t rc = 0;

    rc = rcl_subscription_init(
      &subscriber_handle, &this->uros_node.node_handle,
      type_support, topic_name, &subscriber_options);
    this->uros_node.add_subscription(&subscriber_handle, &msg, cb);
    return rc;
  }

private:
//   ROSTopicMsgT & msg;
//   rclc_callback_t cb;

  uROSNode & uros_node;

  rcl_subscription_t subscriber_handle{0};
  rcl_subscription_options_t subscriber_options;
  const rosidl_message_type_support_t * type_support;
  const char * topic_name;
};

#endif  /* _UROSTOPIC_HPP_ */
