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
// The class to represent a DOS-GIS ring shape.

#include "gis_ring.h"

#include <sstream>

namespace luolc {
namespace dosgis {

GisRing::GisRing() = default;

GisRing::GisRing(const Args &args) : GisPolyline(args) {
}

bool GisRing::IsCover(const GisPoint &point) const {
  auto x = point.Point()->x;
  auto y = point.Point()->y;

  bool odd_node = false;
  auto length = static_cast<int>(vertices_.size());

  for (int i = 0, j = length - 1; i < length; ++i) {
    if (((vertices_[i].y < y && vertices_[j].y >= y) || (vertices_[j].y < y && vertices_[i].y >= y))
        && (vertices_[i].x <= x || vertices_[j].x <= x)) {
      odd_node ^= (vertices_[i].x + (y - vertices_[i].y) / (vertices_[j].y - vertices_[i].y)
          * (vertices_[j].x - vertices_[i].x) < x);
    }
    j = i;
  }

  return odd_node;
}

const std::string GisRing::ToString() const {
  std::ostringstream oss;

  oss << "ring " << id_ << " " << VerticesString() << ", name=" << name_
      << ", length=" << length_ << ", area=" << area_;

  return oss.str();
}

const std::string GisRing::VerticesString() const {
  std::ostringstream oss;

  oss << "[";
  for (const auto &point : vertices_) oss << "[" << point.x << "," << point.y << "], ";
  if (!vertices_.empty()) oss << "[" << vertices_.front().x << "," << vertices_.front().y << "]";
  oss << "]";

  return oss.str();
}

} // namespace dosgis
} // namespace luolc
