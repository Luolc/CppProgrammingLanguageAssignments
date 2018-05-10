// Polyline - Assignment 4 for course Programming Language
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
// The class to represent a polyline.

#include "polyline.h"

#include <algorithm>

namespace luolc {
namespace graphics {

Polyline::Polyline() = default;

Polyline::Polyline(const std::vector<Point> &vertices) {
  for (int i = 0; i < vertices.size() - 1; ++i) {
    lines_.emplace_back(vertices[i], vertices[i + 1]);
  }
}

double Polyline::Length() const {
  double result = 0;

  for (const auto &l: lines_) result += l.Length();

  return result;
}

unsigned long Polyline::Count() const {
  return lines_.size();
}

std::vector<Point> Polyline::GetKDividingPoints(int k) const {
  if (k < 2) return std::vector<Point>();

  auto result = std::vector<Point>();
  auto seg_length = Length() / k;
  double buffer = 0;

  for (const auto &l: lines_) {
    auto start = l.Vertex1();
    auto end = l.Vertex2();
    auto distance = l.Length();
    buffer += distance;

    if (distance == 0) continue;

    auto dx = end.x - start.x;
    auto dy = end.y - start.y;

    while (buffer > seg_length) {
      buffer -= seg_length;

      auto t = (distance - buffer) / distance;
      auto x = start.x + t * dx;
      auto y = start.y + t * dy;

      result.emplace_back(x, y);
    }
  }

  while (result.size() >= k) result.pop_back(); // avoid unexpected point due to precision problem
  return result;
}

bool Polyline::Intersect(const Line &line) const {
  return std::any_of(lines_.begin(),
                     lines_.end(),
                     [&line](const Line &l) { return l.Intersect(line); });
}

} // namespace polyline
} // namespace luolc
