// DOS-GIS - Assignment 6 for course Programming Language
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
// The class to represent a DOS-GIS point shape.

#include "gis_point.h"

#include <sstream>

#include "../util/string_util.hpp"

namespace luolc {
namespace dosgis {

GisPoint::GisPoint() = default;

GisPoint::GisPoint(const Args &args) {
  point_ = ParseArgs(args);
}

const graphics::Point *GisPoint::Point() const {
  return &point_;
}

void GisPoint::Update(const Args &args) {
  point_ = ParseArgs(args);
}

void GisPoint::Move(const Args &args) {
  auto p = ParseArgs(args);
  point_.x += p.x;
  point_.y += p.y;
}

const std::string GisPoint::ToString() const {
  std::ostringstream oss;
  oss << "point " << id_ << " [" << point_.x << "," << point_.y << "], name=" << name_;
  return oss.str();
}

bool GisPoint::EqualTo(const GisPoint &point) const {
  return point_.IsCloseTo(point.point_);
}

const graphics::Point GisPoint::ParseArgs(const AbstractGisShape::Args &args) const {
  auto coordinates = Split(args.front(), ',');
  auto x = std::stod(coordinates[0]);
  auto y = std::stod(coordinates[1]);
  return graphics::Point(x, y);
}

} // namespace dosgis
} // namespace luolc
