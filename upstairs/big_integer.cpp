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
// The class to support addition operation for huge integers.

#include "big_integer.h"

#include <cstring>
#include <algorithm>
#include <iterator>

namespace luolc {
namespace math {

BigInteger::BigInteger() : length_(1) {
  memset(digits_, 0, kMaxLength * sizeof(int));
}

BigInteger::BigInteger(int num) : length_(0) {
  memset(digits_, 0, kMaxLength * sizeof(int));
  while (num > 0) {
    digits_[length_++] = num % kBase;
    num /= kBase;
  }
  if (length_ == 0) ++length_;
}

BigInteger::BigInteger(const luolc::math::BigInteger &rhs) : length_(rhs.length_) {
  std::copy(rhs.digits_, rhs.digits_ + kMaxLength, digits_);
}

BigInteger::~BigInteger() {
  delete[] digits_;
}

BigInteger &BigInteger::operator=(const luolc::math::BigInteger &rhs) {
  length_ = rhs.length_;
  std::copy(rhs.digits_, rhs.digits_ + kMaxLength, digits_);
  return *this;
}

const BigInteger BigInteger::operator+(const luolc::math::BigInteger &rhs) const {
  BigInteger result(*this);

  const auto max_length = std::max(length_, rhs.length_);
  for (int i = 0; i < max_length; ++i) {
    result.digits_[i] += rhs.digits_[i];
    result.digits_[i + 1] += result.digits_[i] / kBase;
    result.digits_[i] %= kBase;
  }
  result.length_ = max_length;
  if (result.digits_[max_length] > 0) ++result.length_;

  return result;
}

const bool BigInteger::operator<(const BigInteger &rhs) const {
  if (length_ != rhs.length_) return length_ < rhs.length_;
  for (int i = length_ - 1; i >= 0; --i) {
    if (digits_[i] != rhs.digits_[i]) return digits_[i] < rhs.digits_[i];
  }
  return false;
}

const bool BigInteger::operator!=(const BigInteger &rhs) const {
  return *this < rhs || rhs < *this;
}

std::ostream &operator<<(std::ostream &out, const BigInteger &num) {
  for (int i = num.length_ - 1; i >= 0; --i) out << num.digits_[i];
  return out;
}

} // namespace math
} // namespace luolc
