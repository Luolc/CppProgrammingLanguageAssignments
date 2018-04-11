// Goldbach - Assignment 2 for course Programming Language
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
// Class for sieving methods and other related utils.

#include "primes.h"

#include <cstring>

namespace luolc {
namespace goldbach {

Primes::Primes(int segment_size) : segment_size_(segment_size) {
  flag_ = new bool[segment_size + 1];
  EratosthenesSieve(segment_size);
}

Primes::~Primes() {
  delete[] flag_;
};

const bool Primes::IsPrime(Integer x) const {
  return prime_set_.find(x) != prime_set_.end();
}

const std::vector<Integer> Primes::GetPrimes() const {
  return primes_;
}

void Primes::ExpandPrimes() {
  SegmentedSieve();
}

Integer Primes::MaxSize() const {
  return max_size_;
}

void Primes::EratosthenesSieve(int n) {
  memset(flag_, true, (n + 1) * sizeof(bool));
  for (int p = 2; p * p <= n; ++p) {
    if (flag_[p]) {
      for (int x = p * p; x <= n; x += p) {
        flag_[x] = false;
      }
    }
  }

  for (int i = 2; i <= n; ++i) {
    if (flag_[i]) {
      primes_.push_back(i);
      prime_set_.insert(i);
    }
  }

  max_size_ = n;
}

void Primes::SegmentedSieve() {
  auto start = max_size_ + 1;
  memset(flag_, true, segment_size_ * sizeof(bool));
  for (const auto &p: primes_) {
    if (p * p >= start + segment_size_) break;
    for (Integer i = (p - start % p) % p; i < segment_size_; i += p) {
      flag_[i] = false;
    }
  }

  for (int i = 0; i < segment_size_; ++i) {
    if (flag_[i]) {
      primes_.push_back(start + i);
      prime_set_.insert(start + i);
    }
  }

  max_size_ += segment_size_;
}

} // namespace goldbach
} // namespace luolc
