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
// Abstract class representing curve polygons.

#include "OGRCurvePolygon.h"

OGRCurvePolygon::OGRCurvePolygon() = default;

OGRCurvePolygon::OGRCurvePolygon(const OGRCurvePolygon &other) {
  for (auto i = other.begin(); i != other.end(); ++i) {
    curves_.push_back((OGRCurve *) (*i)->Clone());
  }
}

OGRCurvePolygon::~OGRCurvePolygon() {
  for (auto i = 0; i < curves_.size(); ++i) delete curves_[i];
  curves_.clear();
}

OGREnvelope OGRCurvePolygon::GetMBR() const {
  auto result = OGREnvelope();

  for (const auto &i : curves_) {
    result.Merge(i->GetMBR());
  }

  return result;
}

bool OGRCurvePolygon::Equals(const OGRGeometry *other) const {
  if (!TypeEquals(other)) return false;

  auto p = (OGRCurvePolygon *) other;
  for (auto i = begin(), j = p->begin(); i != end() || j != p->end(); ++i, ++j) {
    if (i == end() ^ j == p->end()) return false;
    if (!(*i)->Equals(*j)) return false;
  }

  return true;
}

double OGRCurvePolygon::GetPerimeter() const {
  double result = 0;

  for (const auto &i : curves_) {
    result += i->GetLength();
  }

  return result;
}

OGRCurvePolygon::const_iterator OGRCurvePolygon::begin() const {
  return curves_.begin();
}

OGRCurvePolygon::const_iterator OGRCurvePolygon::end() const {
  return curves_.end();
}
