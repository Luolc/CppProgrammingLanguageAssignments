// Warcraft - Assignment 7 for course Programming Language
//
// The MIT License (MIT)
//
// Copyright (c) 2018 Luolc
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

// Author: luolc.witty@gmail.com (Liangchen Luo)
//
// The event handling methods.

#include "event.h"

#include <algorithm>
#include <vector>

namespace luolc {
namespace warcraft {
namespace event {

int current_time = 0;

std::vector<Message> message_pool;

void SendMessage(const std::string &msg, int city_index, int priority) {
  message_pool.push_back({msg, message_pool.size(), city_index, priority});
}

void PrintMessages() {
  std::sort(message_pool.begin(), message_pool.end(), [](const Message &lhs, const Message &rhs) {
    if (lhs.city_index != rhs.city_index) return lhs.city_index < rhs.city_index;
    if (lhs.priority != rhs.priority) return lhs.priority < rhs.priority;
    return lhs.msg_index < rhs.msg_index;
  });

  auto hour = current_time / 60;
  auto minute = current_time % 60;
  std::for_each(message_pool.begin(), message_pool.end(), [hour, minute](const Message &msg) {
    printf("%03d:%02d %s\n", hour, minute, msg.content.c_str());
  });

  message_pool.clear();
}

void AddTenMinutes() {
  current_time += 10;
}

void Clear() {
  current_time = 0;
  message_pool.clear();
}

} // namespace event
} // namespace warcraft
} // namespace luolc
