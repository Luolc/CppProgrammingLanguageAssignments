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

#ifndef GRAPHICS_LINE_H
#define GRAPHICS_LINE_H

#include "point.h"

namespace luolc {
namespace graphics {

// Defined in this file.
class Line;

// Represents a line.
class Line {
 public:
  // Constructs a line with its vertices.
  Line(const Point &p1, const Point &p2);
  ~Line();

  // Gets the vertices.
  Point *Vertex1();
  Point *Vertex2();

  // Gets the length of the line.
  double Length() const;

  // Checks if the line intersects another line.
  bool Intersect(const Line &line) const;

  // Gets the vector representation of vertex_1 -> vertex_2
  Point Vector() const;

 protected:
  Point vertex_1_;
  Point vertex_2_;
};

} // namespace polyline
} // namespace luolc

#endif //GRAPHICS_LINE_H
