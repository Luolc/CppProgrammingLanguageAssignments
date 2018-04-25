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
// The class to support operations for huge integer.

#ifndef UPSTAIRS_BIG_INTEGER_H
#define UPSTAIRS_BIG_INTEGER_H

#include <iostream>

namespace luolc {
namespace math {

// Defined in this file.
class BigInteger;

// Represents a huge non-negative integer.
class BigInteger {
 public:
  static constexpr int kMaxLength = 2500; // maximal segments count
  static constexpr int kBase = 10; // the upper bound of each segment

  // Constructs a BigInteger in different ways.
  BigInteger();
  BigInteger(int); // NOLINT
  BigInteger(const BigInteger &);
  ~BigInteger();

  // Assigning operator.
  BigInteger &operator=(const BigInteger &);

  // Arithmetic operators.
  const BigInteger operator+(const BigInteger &) const;

  // Comparision operators.
  const bool operator<(const BigInteger &) const;
  const bool operator!=(const BigInteger &) const;

  // I/O stream operators.
  friend std::ostream &operator<<(std::ostream &, const BigInteger &);

 private:
  int length_; // current length of the segments
  int *digits_ = new int[kMaxLength]; // segments
};

} // namespace math
} // namespace luolc

#endif //UPSTAIRS_BIG_INTEGER_H
