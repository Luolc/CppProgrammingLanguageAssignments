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
// The class to represent a DOS-GIS polyline shape.

#ifndef DOSGIS_GIS_POLYLINE_H
#define DOSGIS_GIS_POLYLINE_H

#include <string>
#include <vector>

#include "abstract_gis_shape.h"
#include "../graphics/point.h"

namespace luolc {
namespace dosgis {

// Defined in this file.
class GisPolyline;

// Represents a DOS-GIS polyline shape.
class GisPolyline : public AbstractGisVertices {
 public:
  // Constructs a GisPolyline with a list of string arg.
  GisPolyline();
  explicit GisPolyline(const Args &args); // args=["x1,y1,x2,y2,x3,y3"]

  void Reset(const Args &args);

  // Operations
  void Update(const Args &args) override; // args=["index", "x,y"]
  void Move(const Args &args) override; // args=["index", "dx,dy"]
  void Remove(const Args &args) override; // args=["index"]

  const std::string ToString() const override;

 protected:
  std::vector<graphics::Point> vertices_;

  // Parses args to a pair of <index, points>.
  const std::pair<int, std::vector<graphics::Point>> ParseArgs(const Args &args) const;
};

} // namespace dosgis
} // namespace luolc

#endif //DOSGIS_GIS_POLYLINE_H
