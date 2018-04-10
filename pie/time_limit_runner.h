// Pie - Assignment 1 for course Programming Language
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
// Class for running repeat procedures within a time limit.

#ifndef PIE_TIME_LIMIT_RUNNER_H
#define PIE_TIME_LIMIT_RUNNER_H

#include <functional>

namespace luolc {
namespace pie {

// By "millisecond", the time unit should be used precisely.
typedef long long int Millis;

// Defined in this file.
class TimeLimitRunner;

// This class keeps executing repeat procedures until reaching a specific time limit. It is
// helpful for some tasks with time limitation.
class TimeLimitRunner {
 public:
  // Constructs a TimeLimitRunner that keeps executing repeat procedures with step_size times
  // per iteration until reaching the given time limit.
  TimeLimitRunner(Millis limit, int step_size);
  ~TimeLimitRunner();

  // Starts to run the given executable action until reaching the time limit.
  Millis Run(const std::function<void()> &action);

 private:
  Millis limit_;
  int step_size_;
};

} // namespace pie
} // namespace luolc

#endif // PIE_TIME_LIMIT_RUNNER_H
