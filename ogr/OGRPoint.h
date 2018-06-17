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

#ifndef OGR_OGRPOINT_H
#define OGR_OGRPOINT_H

#include "OGRGeometry.h"

// Defined in this file.
class OGRPoint;

// Point class.
class OGRPoint : public OGRGeometry {
 public:
  OGRPoint();
  OGRPoint(double x, double y);
  OGRPoint(const OGRPoint &);
  ~OGRPoint();

  const char *GetGeometryType() const override;
  OGREnvelope GetMBR() const override;
  void Copy(const OGRGeometry &) override;
  OGRGeometry *Clone() const override;
  bool Equals(const OGRPoint &) const;
  bool Equals(const OGRGeometry *) const override;
  void ImportFromWkt(std::string path) override;
  std::string ToString() const override;

  // Returns x.
  double GetX() const;

  // Returns y.
  double GetY() const;

  // Gets the distance to another point.
  double GetDistanceTo(const OGRPoint &) const;

 private:
  double x_;
  double y_;
};

#endif //OGR_OGRPOINT_H
