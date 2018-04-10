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
// Class for estimating the value of pie using Monte-Carlo Method.

#ifndef PIE_MONTE_CARLO_TESTER_H
#define PIE_MONTE_CARLO_TESTER_H

#include <functional>

namespace luolc {
namespace pie {

// Counts the random events.
typedef long long int Count;

// Defined in this file.
class MonteCarloTester;

// This class helps to test a series of independent events and estimate the probability of
// such an event.
class MonteCarloTester {
 public:
  // Constructs a MonteCarloTester with a given tester which emits a test result at each calling.
  explicit MonteCarloTester(const std::function<bool()> &tester);
  ~MonteCarloTester();

  // Runs a single test and returns the result.
  bool Test();

  // Returns the estimated probability.
  double Probability();

 private:
  std::function<bool()> tester_;

  Count n_happened_ = 0;
  Count n_total_ = 0;
};

} // namespace pie
} // namespace luolc

#endif //PIE_MONTE_CARLO_TESTER_H
