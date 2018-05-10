// Polyline - Assignment 4 for course Programming Language
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
// The class to represent a polyline.

#ifndef POLYLINE_POLYLINE_H
#define POLYLINE_POLYLINE_H

#include <vector>

#include "line.h"
#include "point.h"

namespace luolc {
namespace graphics {

// Defined in this file.
class Polyline;

// Represents a polyline.
class Polyline {
 public:
  // Constructs a polyline with its vertices.
  Polyline();
  explicit Polyline(const std::vector<Point> &vertices);

  // Gets the total length of the polyline.
  double Length() const;

  // Gets the count of the lines.
  unsigned long Count() const;

  // Gets (k - 1) k-dividing points of the polyline.
  std::vector<Point> GetKDividingPoints(int k) const;

  // Checks if the polyline intersects another line.
  bool Intersect(const Line &line) const;

 private:
  std::vector<Line> lines_;
};

} // namespace polyline
} // namespace luolc

#endif //POLYLINE_POLYLINE_H
