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
// Concrete representation of a multi-vertex line.

#include "OGRLineString.h"

#include <algorithm>
#include <sstream>

OGRLineString::OGRLineString() = default;

OGRLineString::OGRLineString(const OGRLineString &other) {
  for (auto i = other.begin(); i != other.end(); ++i) {
    points_.emplace_back(i->GetX(), i->GetY());
  }
}

OGRLineString::~OGRLineString() = default;

const char *OGRLineString::GetGeometryType() const {
  return "OGRLineString";
}

OGREnvelope OGRLineString::GetMBR() const {
  auto envelop = OGREnvelope();

  for (const auto &item : points_) {
    envelop.MinX = std::min(envelop.MinX, item.GetX());
    envelop.MaxX = std::max(envelop.MaxX, item.GetX());
    envelop.MinY = std::min(envelop.MinY, item.GetY());
    envelop.MaxY = std::max(envelop.MaxY, item.GetY());
  }

  return envelop;
}

void OGRLineString::Copy(const OGRGeometry &other) {
  auto p = (OGRLineString *) other.Clone();
  *this = *p;
  delete p;
}

OGRGeometry *OGRLineString::Clone() const {
  return new OGRLineString(*this);
}

bool OGRLineString::Equals(const OGRLineString &other) const {
  return Equals(&other);
}

bool OGRLineString::Equals(const OGRGeometry *other) const {
  if (!TypeEquals(other)) return false;

  auto p = (OGRLineString *) other;
  for (auto i = begin(), j = p->begin(); i != end() || j != p->end(); ++i, ++j) {
    if (i == end() ^ j == p->end()) return false;
    if (!i->Equals(*j)) return false;
  }

  return true;
}

void OGRLineString::ImportFromWkt(std::string path) {
}

std::string OGRLineString::ToString() const {
  std::ostringstream oss;

  oss << "LineString (";
  for (auto i = begin(); i != end(); ++i) {
    if (i != begin()) oss << ", ";
    oss << i->GetX() << " " << i->GetY();
  }
  oss << ")";

  return oss.str();
}

double OGRLineString::GetLength() const {
  double length = 0;

  for (auto i = begin(); (i + 1) != end(); ++i) {
    auto next = i + 1;
    length += i->GetDistanceTo(*next);
  }

  return length;
}
