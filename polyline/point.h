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
// The class to represent a point.

#ifndef POLYLINE_POINT_H
#define POLYLINE_POINT_H

namespace luolc {
namespace graphics {

// Defined in this file.
class Point;

// Represents a point.
class Point {
 public:
  // Coordinates
  const double x;
  const double y;

  // Constructs a Point with its coordinates (default 0, 0).
  Point();
  Point(double x, double y);
  Point(const Point &);
  ~Point();

  // Gets the distance to another point.
  double GetDistanceTo(const Point &) const;
};

} // namespace polyline
} // namespace luolc

#endif //POLYLINE_POINT_H
