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
// A collection of OGRCurve.

#include "OGRMultiCurve.h"

#include <sstream>

OGRMultiCurve::OGRMultiCurve() = default;

OGRMultiCurve::OGRMultiCurve(const OGRMultiCurve &other) : OGRGeometryCollection(other) {
}

const char *OGRMultiCurve::GetGeometryType() const {
  return "OGRMultiCurve";
}

void OGRMultiCurve::Copy(const OGRGeometry &other) {
  auto p = (OGRMultiCurve *) other.Clone();
  *this = *p;
}

OGRGeometry *OGRMultiCurve::Clone() const {
  return new OGRMultiCurve(*this);
}

bool OGRMultiCurve::Equals(const OGRMultiCurve &other) const {
  return OGRGeometryCollection::Equals(&other);
}

void OGRMultiCurve::ImportFromWkt(std::string path) {
}

std::string OGRMultiCurve::ToString() const {
  std::ostringstream oss;

  oss << "OGRMultiCurve (";
  for (auto i = begin(); i != end(); ++i) {
    if (i != begin()) oss << ", ";
    oss << (*i)->ToString();
  }
  oss << ")";

  return oss.str();
}

const char *OGRMultiCurve::ItemType() const {
  return "OGRCurve";
}
