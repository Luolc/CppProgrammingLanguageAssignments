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
// Abstract class representing curve polygons.

#ifndef OGR_OGRCURVEPOLYGON_H
#define OGR_OGRCURVEPOLYGON_H

#include "OGRSurface.h"

#include <vector>

#include "OGRCurve.h"

// Defined in this file.
class OGRCurvePolygon;

// Abstract class representing curve polygons.
// Note: I don't know how to implement this class so I just left it abstract.
class OGRCurvePolygon : public OGRSurface {
 public:
  typedef std::vector<OGRCurve *>::const_iterator const_iterator;

  OGRCurvePolygon();
  OGRCurvePolygon(const OGRCurvePolygon &);
  ~OGRCurvePolygon();

  OGREnvelope GetMBR() const override;
  bool Equals(const OGRGeometry *) const override;

  // Returns the perimeter of the polygon.
  double GetPerimeter() const;

  const_iterator begin() const;
  const_iterator end() const;

 protected:
  std::vector<OGRCurve *> curves_;
};

#endif //OGR_OGRCURVEPOLYGON_H
