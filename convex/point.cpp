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
// The class to represent a point.

#include "point.h"

#include <cmath>

namespace luolc {
namespace graphics {

Point::Point() : x(0), y(0) {
}

Point::Point(double x, double y) : x(x), y(y) {
}

Point::~Point() = default;

const Point Point::operator-() const {
  return Point(-x, -y);
}

const Point Point::operator+(const Point &point) const {
  return Point(x + point.x, y + point.y);
}

const Point Point::operator-(const Point &point) const {
  return *this + (-point);
}

const double Point::Dot(const Point &point) const {
  return x * point.x + y * point.y;
}

const double Point::Det(const Point &point) const {
  return x * point.y - point.x * y;
}

double Point::GetDistanceTo(const Point &point) const {
  auto dx = point.x - x;
  auto dy = point.y - y;
  auto square_sum = dx * dx + dy * dy;
  return square_sum > 0 ? std::sqrt(square_sum) : 0; // smooth expr to avoid minus square root
}
bool Point::IsCloseTo(const Point &point) const {
  return abs(GetDistanceTo(point)) < EPS;
}

} // namespace polyline
} // namespace luolc
