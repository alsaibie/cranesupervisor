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
#include <rcl_action/rcl_action.h>
}

class uROSTopicBase_ {
   public:
    uint32_t initialize() {
        uint32_t rc = 0;
        rc = rcl_publisher_init(&publisher_handle, &node_handle, type_support, topic_name, &publisher_options);
        return rc;
    }

   protected:
    uROSTopicBase_(const char *name_, const rcl_node_t &nh_, const rosidl_message_type_support_t *type_support_) : node_handle(nh_), type_support(type_support_) {
        topic_name = name_;
        publisher_options = rcl_publisher_get_default_options();
        publisher_options.qos.reliability = RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT;
    }

    virtual ~uROSTopicBase_() {}

    const rcl_node_t &node_handle;

    rcl_publisher_t publisher_handle{0};
    rcl_publisher_options_t publisher_options;
    const rosidl_message_type_support_t *type_support;
    const char *topic_name;

   private:
};

template <typename ROSTopicMsgT>
class uROSTopicPublisher : public uROSTopicBase_ {
   public:
    uROSTopicPublisher(const char *name_, const rcl_node_t &nh_, const rosidl_message_type_support_t *type_support_) : uROSTopicBase_(name_, nh_, type_support_) {
    }

    uint32_t publish(ROSTopicMsgT &msg) {
        uint32_t rc = 0;
        rc = rcl_publish(&publisher_handle, (const void *)&msg, NULL);
        return rc;
    }
};

#endif  // _UROSTOPIC_HPP_