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
// The class to represent a DOS-GIS polygon shape.

#ifndef DOSGIS_GIS_POLYGON_H
#define DOSGIS_GIS_POLYGON_H

#include <unordered_map>

#include "abstract_gis_shape.h"
#include "gis_ring.h"
#include "../graphics/point.h"

namespace luolc {
namespace dosgis {

// Defined in this file.
class GisPolygon;

// Represents a DOS-GIS polygon shape.
class GisPolygon : public AbstractGisVertices {
 public:
  // Constructs a GisPolygon with a list of string arg.
  GisPolygon();
  explicit GisPolygon(const Args &args); // args=["outer/inner", "x1,y1,x2,y2,x3,y3,x4,y4"]

  // Operations
  void Update(const Args &args) override; // args=["outer/inner", "index", "x,y"]
  void Move(const Args &args) override; // args=["outer/inner", "index", "dx,dy"]
  void Remove(const Args &args) override; // args=["outer/inner", "index"]
  void Reset(const std::string &which, const Args &args); // args=["x1,y1,x2,y2,x3,y3,x4,y4"]

  const std::string ToString() const override;

  // Checks whether the point is inside the polygon.
  bool IsCover(const GisPoint &point) const;

 private:
  GisRing inner_;
  GisRing outer_;
  std::unordered_map<std::string, GisRing *> rings_;

  // Represents a branch of update arguments.
  struct Arguments;

  // Parses args.
  const Arguments ParseArgs(const Args &args) const;
};

struct GisPolygon::Arguments {
  // inner or outer
  std::string which;

  Args ring_args;
};

} // namespace dosgis
} // namespace luolc

#endif //DOSGIS_GIS_POLYGON_H
