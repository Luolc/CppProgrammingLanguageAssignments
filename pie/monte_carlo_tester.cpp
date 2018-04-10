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

#include "monte_carlo_tester.h"

namespace luolc {
namespace pie {

MonteCarloTester::MonteCarloTester(const std::function<bool()> &tester) {
  this->tester_ = tester;
}

MonteCarloTester::~MonteCarloTester() = default;

bool MonteCarloTester::Test() {
  auto result = this->tester_();

  if (result) ++this->n_happened_;
  ++this->n_total_;

  return result;
}

double MonteCarloTester::Probability() {
  return double(this->n_happened_) / this->n_total_;
}

} // namespace pie
} // namespace luolc
