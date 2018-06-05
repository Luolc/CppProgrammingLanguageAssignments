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

#ifndef DOSGIS_GIS_POINT_H
#define DOSGIS_GIS_POINT_H

#include <string>
#include <vector>

#include "abstract_gis_shape.h"
#include "../graphics/point.h"

namespace luolc {
namespace dosgis {

// Defined in this file.
class GisPoint;

// Represents a DOS-GIS point shape.
class GisPoint : public AbstractGisShape {
 public:
  // Constructs a GisPoint with a list of string arg.
  GisPoint();
  explicit GisPoint(const Args &args); // args=["x,y"]

  // Gets the inside graphics point.
  const graphics::Point *Point() const;

  // Operations
  void Update(const Args &args) override; // args=["x,y"]
  void Move(const Args &args) override; // args=["dx,dy"]

  const std::string ToString() const override;

  // Checks whether the two points are close (means equal).
  bool IsCloseTo(const GisPoint &) const;

 private:
  graphics::Point point_;

  // Parses args to a point. Note that all the args are sth like ["x,y"]
  const graphics::Point ParseArgs(const Args &args) const;
};

} // namespace dosgis
} // namespace luolc

#endif //DOSGIS_GIS_POINT_H
