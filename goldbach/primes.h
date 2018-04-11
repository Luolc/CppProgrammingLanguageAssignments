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

#ifndef GOLDBACH_PRIMES_H
#define GOLDBACH_PRIMES_H

#include <vector>
#include <set>

namespace luolc {
namespace goldbach {

// In case we have to change the type to support bigger numbers.
typedef long long int Integer;

// Defined in this file.
class Primes;

// This class can sieve primes using different algorithms, check a number and iterate through
// sieved primes.
class Primes {
 public:
  // Constructs a Primes with a segment_size for the segmented sieving.
  explicit Primes(int segment_size);
  ~Primes();

  // Whether x is a prime.
  // Note that this method only work for x in range [1, MaxSize]. If the argument x is out of
  // range, then the return value is always false.
  const bool IsPrime(Integer x) const;

  // Gets all the primes we have collected.
  const std::vector<Integer> GetPrimes() const;

  // Expands the bag-of-primes using segmented Eratosthenes sieving.
  void ExpandPrimes();

  // Indicates that we have collected all the primes in range [1, MaxSize].
  Integer MaxSize() const;

 private:
  int segment_size_;

  Integer max_size_;

  bool *flag_; // indicator of primes; flag[i] is true if i is a prime

  std::vector<Integer> primes_; // the list of the collected primes
  std::set<Integer> prime_set_; // the set of the collected primes

  // Sieve of Eratosthenes.
  // Ref: https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
  void EratosthenesSieve(int n);

  // Segmented Sieve of Eratosthenes
  // Ref: Jonathan Sorenson, "An introduction to prime number sieves", Computer sciences
  //   technical report #909.1990.
  void SegmentedSieve();
};

} // namespace goldbach
} // namespace luolc

#endif //GOLDBACH_PRIMES_H
