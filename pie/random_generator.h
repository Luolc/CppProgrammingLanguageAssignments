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
// Class for generating random real numbers.

#ifndef PIE_RANDOM_POINT_GENERATOR_H
#define PIE_RANDOM_POINT_GENERATOR_H

#include <random>

namespace luolc {
namespace pie {

// Defined in this file.
class UniformRandomGenerator;

// This class generates random real number in a uniform distribution.
class UniformRandomGenerator {
 public:
  // Constructs a UniformRandomGenerator which generates random number in the range [left, right]
  // in a uniform distribution.
  UniformRandomGenerator(double left, double right);
  ~UniformRandomGenerator();

  // Generates the next random real number;
  double Generate();

 private:
  std::default_random_engine generator_;
  std::uniform_real_distribution<double> distribution_;
};

} // namespace pie
} // namespace luolc

#endif //PIE_RANDOM_POINT_GENERATOR_H
