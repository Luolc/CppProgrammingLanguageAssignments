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
// A collection of non-overlapping OGRPolygon.

#include "OGRMultiPolygon.h"

#include <algorithm>
#include <fstream>
#include <sstream>

#include "OGRPolygon.h"

OGRMultiPolygon::OGRMultiPolygon() = default;

OGRMultiPolygon::OGRMultiPolygon(const OGRMultiPolygon &other) : OGRMultiSurface(other) {
}

const char *OGRMultiPolygon::GetGeometryType() const {
  return "OGRMultiPolygon";
}

void OGRMultiPolygon::Copy(const OGRGeometry &other) {
  auto p = (OGRMultiPolygon *) other.Clone();
  *this = *p;
}

OGRGeometry *OGRMultiPolygon::Clone() const {
  return new OGRMultiPolygon(*this);
}

bool OGRMultiPolygon::Equals(const OGRMultiPolygon &other) const {
  return OGRGeometryCollection::Equals(&other);
}

void OGRMultiPolygon::ImportFromWkt(std::string path) {
  std::ifstream in(path.c_str());
  std::string line;
  std::getline(in, line);

  // MultiPolygon (((
  //               ↑ position=14
  line = line.substr(14);
  line.erase(line.size() - 1);

  auto closed = 0;
  unsigned long left = 0;
  for (unsigned long right = 0; right < line.size(); ++right) {
    if (closed == 0 && line[right] == '(') left = right;

    if (line[right] == '(') --closed;
    else if (line[right] == ')') ++closed;

    if (closed == 0 && line[right] == ')') {
      auto sub = line.substr(left, right - left + 1);
      sub = std::string("Polygon ") + sub;
      auto polygon = new OGRPolygon();
      polygon->ImportFromWktText(sub);

      container_.push_back(polygon);

      left = right + 1;
    }
  }
}

std::string OGRMultiPolygon::ToString() const {
  std::ostringstream oss;

  oss << "MultiPolygon (";
  for (auto i = begin(); i != end(); ++i) {
    if (i != begin()) oss << ", ";
    auto p = (OGRPolygon *) *i;
    auto polygon_str = p->ToString();
    // Polygon (
    //         ↑ position=11
    oss << polygon_str.substr(8);
  }
  oss << ")";

  return oss.str();
}

double OGRMultiPolygon::GetArea() const {
  double result = 0;

  for (const auto &i : container_) {
    result += ((OGRPolygon *) i)->GetArea();
  }

  return result;
}

double OGRMultiPolygon::GetPerimeter() const {
  double result = 0;

  for (const auto &i : container_) {
    result += ((OGRPolygon *) i)->GetPerimeter();
  }

  return result;
}

bool OGRMultiPolygon::Contains(const OGRGeometry *item) const {
  return std::any_of(
      begin(),
      end(),
      [&item](const OGRGeometry *polygon) { return ((OGRPolygon *) polygon)->Contains(item); });
}

const char *OGRMultiPolygon::ItemType() const {
  return "OGRPolygon";
}
