// Utilities for course Programming Language
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
// The class to represent a line.

#include "line.h"

namespace luolc {
namespace graphics {

Line::Line(const Point &p1, const Point &p2) : vertex_1_(p1), vertex_2_(p2) {
}

Line::~Line() = default;

const bool Line::operator<(const Line &line) const {
  if (vertex_1_ < line.vertex_1_ || line.vertex_1_ < vertex_1_) return vertex_1_ < line.vertex_1_;
  else return vertex_2_ < line.vertex_2_;
}

Point Line::Vertex1() const {
  return vertex_1_;
}

Point Line::Vertex2() const {
  return vertex_2_;
}

double Line::Length() const {
  return vertex_1_.GetDistanceTo(vertex_2_);
}

bool Line::Intersect(const Line &line) const {
  // ref: https://stackoverflow.com/questions/4977491/determining-if-two-line-segments-intersect/4977569#4977569
  // L0: (x, y) = (x00, y00) + t1 * (x01, y01)
  // L1: (x, y) = (x10, y10) + t1 * (x11, y11)
  auto x00 = vertex_1_.x;
  auto y00 = vertex_1_.y;
  auto x01 = vertex_2_.x - vertex_1_.x;
  auto y01 = vertex_2_.y - vertex_1_.y;
  auto x10 = line.vertex_1_.x;
  auto y10 = line.vertex_1_.y;
  auto x11 = line.vertex_2_.x - line.vertex_1_.x;
  auto y11 = line.vertex_2_.y - line.vertex_1_.y;

  // Computes the solution of
  // | x00 - x10 |   | x11  x01 | | t2|
  // | y00 - y10 | = | y11  y01 | |-t1|

  //         |x11 x01|
  // d = det(|y11 y01|) = x11 * y01 - x01 * y11
  auto d = x11 * y01 - x01 * y11;

  // parallel
  if (d == 0) return false;

  auto t1 = 1 / d * -(-(x00 - x10) * y11 + (y00 - y10) * x11);
  auto t2 = 1 / d * ((x00 - x10) * y01 - (y00 - y10) * x01);

  // t1 in [0, 1] and t2 in [0, 1]
  return t1 >= 0 && t1 <= 1 && t2 >= 0 && t2 <= 1;
}

Point Line::Vector() const {
  return vertex_2_ - vertex_1_;
}

} // namespace graphics
} // namespace luolc
