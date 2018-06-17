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
// Abstract base class for all geometry classes.

#include "OGRGeometry.h"

#include <cmath>
#include <cstdio>
#include <cstring>

int OGRGeometry::incremental_index = 0;

OGRGeometry::OGRGeometry() : id_(incremental_index++) {
}

OGRGeometry::~OGRGeometry() = default;

int OGRGeometry::GetID() const {
  return id_;
}

bool OGRGeometry::Equals(const OGRGeometry &other) const {
  return Equals(&other);
}

bool OGRGeometry::IsClose(double x, double y) {
  auto delta = std::abs(x - y);
  return delta < EPS && delta > -EPS;
}

bool OGRGeometry::TypeEquals(const OGRGeometry *other) const {
  return strcmp(GetGeometryType(), other->GetGeometryType()) == 0;
}

void OGRGeometry::ExportToWkt(std::string path) {
  auto fp = std::fopen(path.c_str(), "w");
  fprintf(fp, "%s", ToString().c_str());
}

std::string OGRGeometry::ToString() const {
  return GetGeometryType();
}
