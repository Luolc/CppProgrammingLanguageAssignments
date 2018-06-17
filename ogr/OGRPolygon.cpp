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
// Concrete class representing polygons.

#include "OGRPolygon.h"

#include <algorithm>
#include <fstream>
#include <sstream>

#include "string_util.hpp"

OGRPolygon::OGRPolygon() = default;

OGRPolygon::OGRPolygon(const OGRPolygon &other) : OGRCurvePolygon(other) {
}

const char *OGRPolygon::GetGeometryType() const {
  return "OGRPolygon";
}

void OGRPolygon::Copy(const OGRGeometry &other) {
  auto p = (OGRPolygon *) other.Clone();
  *this = *p;
}

OGRGeometry *OGRPolygon::Clone() const {
  return new OGRPolygon(*this);
}

bool OGRPolygon::Equals(const OGRPolygon &other) const {
  return OGRCurvePolygon::Equals(&other);
}

void OGRPolygon::ImportFromWkt(std::string path) {
  std::ifstream in(path.c_str());
  std::string line;
  std::getline(in, line);

  ImportFromWktText(line);
}

void OGRPolygon::ImportFromWktText(std::string text) {
  // Polygon ((-4.0 -4.0, 4 -4, 4.0 4.0, -4 4), (-2.0 -2.0, 2 -2, 2.0 2.0, -2 2))
  //          ↑ position=9
  auto line = text.substr(9);
  // (-4.0 -4.0, 4 -4, 4.0 4.0, -4 4), (-2.0 -2.0, 2 -2, 2.0 2.0, -2 2)
  line.erase(line.size() - 1);

  // ["(-4.0 -4.0, 4 -4, 4.0 4.0, -4 4", ", (-2.0 -2.0, 2 -2, 2.0 2.0, -2 2"]
  auto rings = Split(line, ')');
  for (auto i = 0; i < rings.size(); ++i) {
    std::string str_clean;
    if (i == 0) str_clean = rings[i].substr((1));
    else str_clean = rings[i].substr(3);
    auto points_str = Split(str_clean, ',');

    auto ring = new OGRLinearRing();
    for (const auto &s : points_str) {
      auto xy = Split(s, ' ');
      auto x = std::stod(xy[0]);
      auto y = std::stod(xy[1]);
      ring->AddPoint(x, y);
    }
    curves_.push_back(ring);
  }
}

std::string OGRPolygon::ToString() const {
  std::ostringstream oss;

  oss << "Polygon (";
  for (auto i = begin(); i != end(); ++i) {
    if (i != begin()) oss << ", ";
    auto p = (OGRLinearRing *) *i;
    auto ring_str = p->ToString();
    // OGRLinearRing (
    //               ↑ position=14
    oss << ring_str.substr(14);
  }
  oss << ")";

  return oss.str();
}

double OGRPolygon::GetArea() const {
  double result = 0;

  if (!curves_.empty()) result += ((OGRLinearRing *) curves_.front())->GetArea();
  for (auto i = 1; i < curves_.size(); ++i) {
    result -= ((OGRLinearRing *) curves_[i])->GetArea();
  }

  return result;
}

const OGRLinearRing *OGRPolygon::GetExteriorRing() const {
  return (OGRLinearRing *) curves_.front();
}

bool OGRPolygon::Contains(const OGRGeometry *item) const {
  if (curves_.empty()) return false;

  auto result = ((OGRLinearRing *) curves_.front())->Contains(item);

  if (strcmp(item->GetGeometryType(), "OGRPoint") == 0) {
    for (auto i = 1; i < curves_.size(); ++i) {
      result &= !((OGRLinearRing *) curves_[i])->Contains(item);
    }
  } else if (strcmp(item->GetGeometryType(), "OGRLineString") == 0) {
    auto ring = (OGRLineString *) item;
    for (auto i = 1; i < curves_.size(); ++i) {
      auto inner = (OGRLinearRing *) curves_[i];
      result &= !std::any_of(
          ring->begin(),
          ring->end(),
          [&inner](const OGRPoint &point) { return inner->Contains((OGRGeometry *) &point); });
    }
  } else if (strcmp(item->GetGeometryType(), "OGRPolygon") == 0) {
    auto polygon = (OGRPolygon *) item;
    for (auto i = 1; i < curves_.size(); ++i) {
      auto inner = (OGRLinearRing *) curves_[i];
      result &= !std::any_of(
          inner->begin(),
          inner->end(),
          [&polygon](const OGRPoint &point) { return polygon->Contains((OGRGeometry *) &point); });
    }
  }

  return result;
}
