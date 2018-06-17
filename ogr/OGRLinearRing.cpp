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
// Concrete representation of a closed ring.

#include "OGRLinearRing.h"

#include <algorithm>
#include <sstream>
#include <cmath>
#include <cstring>

#include "OGRPolygon.h"

OGRLinearRing::OGRLinearRing() = default;

OGRLinearRing::OGRLinearRing(const OGRLinearRing &other) : OGRLineString(other) {
}

OGRLinearRing::~OGRLinearRing() = default;

const char *OGRLinearRing::GetGeometryType() const {
  return "OGRLinearRing";
}

void OGRLinearRing::Copy(const OGRGeometry &other) {
  auto p = (OGRLinearRing *) other.Clone();
  *this = *p;
  delete p;
}

OGRGeometry *OGRLinearRing::Clone() const {
  return new OGRLinearRing(*this);
}

bool OGRLinearRing::Equals(const OGRLinearRing &other) const {
  return OGRLineString::Equals(&other);
}

void OGRLinearRing::ImportFromWkt(std::string path) {
}

std::string OGRLinearRing::ToString() const {
  std::ostringstream oss;

  oss << "OGRLinearRing (";
  for (auto i = begin(); i != end(); ++i) {
    if (i != begin()) oss << ", ";
    oss << i->GetX() << " " << i->GetY();
  }
  oss << ")";

  return oss.str();
}

void OGRLinearRing::CloseRings() {
  if (!points_.begin()->Equals(points_.back())) {
    AddPoint(&points_.front());
  }
}

double OGRLinearRing::GetArea() const {
  double result = 0;

  for (auto i = 0; i < points_.size(); ++i) {
    result += points_[i].GetX() * points_[i + 1].GetY() - points_[i].GetY() * points_[i + 1].GetX();
  }

  return std::abs(result / 2);
}

bool OGRLinearRing::Contains(const OGRGeometry *item) const {
  if (strcmp(item->GetGeometryType(), "OGRPoint") == 0) {
    return Contains((OGRPoint *) item);
  } else if (strcmp(item->GetGeometryType(), "OGRLineString") == 0) {
    auto ring = (OGRLineString *) item;
    return std::all_of(ring->begin(), ring->end(),
                       [this](const OGRPoint &point) { return Contains(&point); });
  } else if (strcmp(item->GetGeometryType(), "OGRPolygon") == 0) {
    auto ring = ((OGRPolygon *) item)->GetExteriorRing();
    return std::all_of(ring->begin(), ring->end(),
                       [this](const OGRPoint &point) { return Contains(&point); });
  } else {
    return false;
  }
}

bool OGRLinearRing::Contains(const OGRPoint *point) const {
  auto x = point->GetX();
  auto y = point->GetY();

  bool odd_node = false;
  auto length = static_cast<int>(points_.size());

  for (int i = 0, j = length - 1; i < length; ++i) {
    if ((points_[i].GetY() < y && points_[j].GetY() >= y
        || points_[j].GetY() < y && points_[i].GetY() >= y)
        && (points_[i].GetX() <= x || points_[j].GetX() <= x)) {
      odd_node ^= (points_[i].GetX()
          + (y - points_[i].GetY())
              / (points_[j].GetY() - points_[i].GetY())
              * (points_[j].GetX() - points_[i].GetX())
          < x);
    }
    j = i;
  }

  return odd_node;
}
