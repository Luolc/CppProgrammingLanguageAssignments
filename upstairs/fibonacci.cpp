// Upstairs - Assignment 3 for course Programming Language
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
// The utilities for computing Fibonacci series.

#include "fibonacci.h"

namespace luolc {
namespace upstairs {

Fibonacci::Fibonacci(int cache_size) {
  answers_ = new luolc::math::BigInteger[cache_size + 1];
}

Fibonacci::~Fibonacci() {
  delete[] answers_;
}

const luolc::math::BigInteger Fibonacci::RecursiveFibonacci(int n) {
  if (n == 1) return 1;
  else if (n == 2) return 2;
  else if (answers_[n] != 0) return answers_[n];
  else return answers_[n] = RecursiveFibonacci(n - 1) + RecursiveFibonacci(n - 2);
}

const luolc::math::BigInteger Fibonacci::IterativeFibonacci(int n) {
  auto x = luolc::math::BigInteger(1);
  auto y = luolc::math::BigInteger(2);

  if (n == 1) return x;

  for (int i = 2; i < n; ++i) {
    auto y_copy = y;
    y = x + y;
    x = y_copy;
  }
  return y;
}

} // namespace upstairs
} // namespace luolc
