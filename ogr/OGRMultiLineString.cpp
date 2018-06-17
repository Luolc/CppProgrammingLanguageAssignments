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
// A collection of OGRLineString.

#include "OGRMultiLineString.h"

#include <sstream>

#include "OGRLineString.h"

OGRMultiLineString::OGRMultiLineString() = default;

OGRMultiLineString::OGRMultiLineString(const OGRMultiLineString &other) : OGRMultiCurve(other) {
}

const char *OGRMultiLineString::GetGeometryType() const {
  return "OGRMultiLineString";
}

void OGRMultiLineString::Copy(const OGRGeometry &other) {
  auto p = (OGRMultiLineString *) other.Clone();
  *this = *p;
}

OGRGeometry *OGRMultiLineString::Clone() const {
  return new OGRMultiLineString(*this);
}

bool OGRMultiLineString::Equals(const OGRMultiLineString &other) const {
  return OGRGeometryCollection::Equals(&other);
}

void OGRMultiLineString::ImportFromWkt(std::string path) {
}

std::string OGRMultiLineString::ToString() const {
  std::ostringstream oss;

  oss << "OGRMultiLineString (";
  for (auto i = begin(); i != end(); ++i) {
    if (i != begin()) oss << ", ";
    std::string line_str = (*i)->ToString();
    // LineString (10 10, 20 20, 30 40)
    //            ↑ position=11
    oss << line_str.substr(11);
  }
  oss << ")";

  return oss.str();
}

double OGRMultiLineString::GetLength() const {
  double result = 0;

  for (const auto &i : container_) {
    result += ((OGRLineString *) i)->GetLength();
  }

  return result;
}

const char *OGRMultiLineString::ItemType() const {
  return "OGRLineString";
}
