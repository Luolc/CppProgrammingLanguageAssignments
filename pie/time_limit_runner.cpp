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

#include "time_limit_runner.h"

#include <chrono>

namespace luolc {
namespace pie {

TimeLimitRunner::TimeLimitRunner(Millis limit, int step_size)
    : limit_(limit), step_size_(step_size) {}

TimeLimitRunner::~TimeLimitRunner() = default;

Millis TimeLimitRunner::Run(const std::function<void()> &action) {
  auto begin = std::chrono::steady_clock::now();
  auto soft_limit = (Millis) (this->limit_ * 0.95);

  while (true) {
    for (int i = 0; i < this->step_size_; ++i) action();
    auto now = std::chrono::steady_clock::now();
    auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(now - begin).count();
    if (delta > soft_limit) return delta;
  }
}

} // namespace pie
} // namespace luolc
