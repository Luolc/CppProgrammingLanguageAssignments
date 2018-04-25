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

#ifndef UPSTAIRS_FIBONACCI_H
#define UPSTAIRS_FIBONACCI_H

#include "big_integer.h"

namespace luolc {
namespace upstairs {

// Defined in this file.
class Fibonacci;

// Class for computing Fibonacci series in iterative or recursive ways.
class Fibonacci {
 public:
  // Constructs a Fibonacci helper class with the given cache_size.
  explicit Fibonacci(int cache_size);
  ~Fibonacci();

  // Computes the value of n-th item of a Fibonacci series, recursively.
  // The answers are cached and the cached value will be returned if exists.
  const luolc::math::BigInteger RecursiveFibonacci(int n);

  // Computes the value of n-th item of a Fibonacci series, iteratively.
  const luolc::math::BigInteger IterativeFibonacci(int n);

 private:
  // The cache of answers. It is necessary for the recursive method.
  luolc::math::BigInteger *answers_;
};

} // namespace upstairs
} // namespace luolc

#endif //UPSTAIRS_FIBONACCI_H
