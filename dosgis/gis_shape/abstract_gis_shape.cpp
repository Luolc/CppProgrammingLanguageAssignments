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
// The base class of a DOS-GIS shape.

#include "abstract_gis_shape.h"

#include <string>
#include <utility>

namespace luolc {
namespace dosgis {

AbstractGisShape::AbstractGisShape() {
  name_ = NULL_VAL;
}

const bool AbstractGisShape::operator<(const AbstractGisShape &shape) const {
  return id_ < shape.id_;
}

void AbstractGisShape::SetId(std::string id) {
  id_ = std::move(id);
}

void AbstractGisShape::SetName(std::string name) {
  name_ = std::move(name);
}

AbstractGisVertices::AbstractGisVertices() {
  length_ = NULL_VAL;
  area_ = NULL_VAL;
}

void AbstractGisVertices::SetArea(std::string area) {
  area_ = std::move(area);
}

void AbstractGisVertices::SetLength(std::string length) {
  length_ = std::move(length);
}

} // namespace dosgis
} // namespace luolc
