// OGR - Assignment 7 for course Programming Language
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
// Simple container for a bounding region.

#include "OGREnvelope.h"

#include <limits>
#include <sstream>
#include <cmath>

OGREnvelope::OGREnvelope() : MinX(std::numeric_limits<double>::infinity()),
                             MaxX(-std::numeric_limits<double>::infinity()),
                             MinY(std::numeric_limits<double>::infinity()),
                             MaxY(-std::numeric_limits<double>::infinity()) {
}

OGREnvelope::OGREnvelope(double min_x, double max_x, double min_y, double max_y)
    : MinX(min_x), MaxX(max_x), MinY(min_y), MaxY(max_y) {
}

std::string OGREnvelope::ToString() const {
  std::ostringstream oss;
  oss << "OGREnvelope[BottomLeft=("
      << MinX << ", " << MinY << "), TopRight=(" << MaxX << ", " << MaxY << ")]";
  return oss.str();
}

void OGREnvelope::Merge(const OGREnvelope &other) {
  MinX = std::min(MinX, other.MinX);
  MaxX = std::max(MaxX, other.MaxX);
  MinY = std::min(MinY, other.MinY);
  MaxY = std::max(MaxY, other.MaxY);
}
