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
// A collection of OGRPoint.

#include "OGRMultiPoint.h"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <cstdio>

#include "OGRPoint.h"

OGRMultiPoint::OGRMultiPoint() = default;

OGRMultiPoint::OGRMultiPoint(const OGRMultiPoint &other) : OGRGeometryCollection(other) {
}

const char *OGRMultiPoint::GetGeometryType() const {
  return "OGRMultiPoint";
}

void OGRMultiPoint::Copy(const OGRGeometry &other) {
  auto p = (OGRMultiPoint *) other.Clone();
  *this = *p;
}

OGRGeometry *OGRMultiPoint::Clone() const {
  return new OGRMultiPoint(*this);
}

bool OGRMultiPoint::Equals(const OGRMultiPoint &other) const {
  return OGRGeometryCollection::Equals(&other);
}

void OGRMultiPoint::ImportFromWkt(std::string path) {
  std::ifstream in(path.c_str());
  std::string line;
  std::getline(in, line);
  auto n_points = std::count(line.begin(), line.end(), '(') - 1;
  if (n_points < 1) return;

  double x;
  double y;
  auto fp = std::fopen(path.c_str(), "r");
  fscanf(fp, "MultiPoint ((%lf %lf)", &x, &y);
  AddGeometry(new OGRPoint(x, y));
  for (auto i = 1; i < n_points; ++i) {
    fscanf(fp, ", (%lf %lf)", &x, &y);
    AddGeometry(new OGRPoint(x, y));
  }
}

std::string OGRMultiPoint::ToString() const {
  std::ostringstream oss;

  oss << "OGRMultiPoint (";
  for (auto i = begin(); i != end(); ++i) {
    if (i != begin()) oss << ", ";
    auto point = (OGRPoint *) *i;
    oss << "(" << point->GetX() << " " << point->GetY() << ")";
  }
  oss << ")";

  return oss.str();
}

const char *OGRMultiPoint::ItemType() const {
  return "OGRPoint";
}


