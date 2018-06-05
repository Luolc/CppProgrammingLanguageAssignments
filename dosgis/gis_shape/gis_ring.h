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

#ifndef DOSGIS_GIS_RING_H
#define DOSGIS_GIS_RING_H

#include <string>

#include "gis_point.h"
#include "gis_polyline.h"

namespace luolc {
namespace dosgis {

// Defined in this file.
class GisRing;

// Represents a DOS-GIS ring shape.
class GisRing : public GisPolyline {
 public:
  // Constructs a GisRing with a list of string arg.
  GisRing();
  explicit GisRing(const Args &args);

  // Checks whether the point is inside the ring.
  bool IsCover(const GisPoint &point) const;

  const std::string ToString() const override;

  // Gets the string representation of the vertices
  // i.e. [[5,6], [7,8], [9,10], [5,6]]
  const std::string VerticesString() const;
};

} // namespace dosgis
} // namespace luolc

#endif //DOSGIS_GIS_RING_H
