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

#ifndef WARCRAFT_EVENT_H
#define WARCRAFT_EVENT_H

#include <string>

namespace luolc {
namespace warcraft {
namespace event {

// Represents an event message.
struct Message {
  std::string content; // the message content
  unsigned long msg_index; // the index in the message pool
  int city_index; // the index of the city where the event takes place
  int priority; // the priority of this message
};

// Sends a message.
void SendMessage(const std::string &msg, int city_index = 0, int priority = 0);

// Prints all the message in the message pool.
void PrintMessages();

// Adds ten minutes for the timer.
void AddTenMinutes();

// Resets event handler.
void Clear();

} // event
} // namespace warcraft
} // namespace luolc

#endif //WARCRAFT_EVENT_H
