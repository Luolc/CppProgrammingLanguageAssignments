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
// Point class.

#include "OGRPoint.h"

#include <sstream>
#include <cmath>
#include <cstdio>

OGRPoint::OGRPoint() = default;

OGRPoint::OGRPoint(double x, double y) : x_(x), y_(y) {
}

OGRPoint::OGRPoint(const OGRPoint &other) {
  x_ = other.x_;
  y_ = other.y_;
}

OGRPoint::~OGRPoint() = default;

const char *OGRPoint::GetGeometryType() const {
  return "OGRPoint";
}

OGREnvelope OGRPoint::GetMBR() const {
  return {x_, x_, y_, y_};
}

void OGRPoint::Copy(const OGRGeometry &other) {
  auto p = (OGRPoint *) other.Clone();
  *this = *p;
  delete p;
}

OGRGeometry *OGRPoint::Clone() const {
  return new OGRPoint(*this);
}

bool OGRPoint::Equals(const OGRPoint &other) const {
  return Equals(&other);
}

bool OGRPoint::Equals(const OGRGeometry *other) const {
  if (!TypeEquals(other)) return false;

  auto p = (OGRPoint *) other;
  return IsClose(x_, p->GetX()) && IsClose(y_, p->GetY());
}

void OGRPoint::ImportFromWkt(std::string path) {
  auto fp = std::fopen(path.c_str(), "r");
  fscanf(fp, "Point (%lf %lf)", &x_, &y_);
}

std::string OGRPoint::ToString() const {
  std::ostringstream oss;
  oss << "Point (" << x_ << " " << y_ << ")";
  return oss.str();
}

double OGRPoint::GetX() const {
  return x_;
}

double OGRPoint::GetY() const {
  return y_;
}

double OGRPoint::GetDistanceTo(const OGRPoint &other) const {
  auto dx = x_ - other.GetX();
  auto dy = y_ - other.GetY();
  auto square_sum = dx * dx + dy * dy;
  return square_sum > 0 ? std::sqrt(square_sum) : 0;
}
