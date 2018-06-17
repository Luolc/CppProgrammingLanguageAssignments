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
// Concrete representation of a closed ring.

#ifndef OGR_OGRLINEARRING_H
#define OGR_OGRLINEARRING_H

#include "OGRLineString.h"

// Defined in this file.
class OGRLinearRing;

// Concrete representation of a closed ring.
class OGRLinearRing : public OGRLineString {
 public:
  OGRLinearRing();
  OGRLinearRing(const OGRLinearRing &);
  ~OGRLinearRing();

  const char *GetGeometryType() const override;
  void Copy(const OGRGeometry &) override;
  OGRGeometry *Clone() const override;
  bool Equals(const OGRLinearRing &) const;
  void ImportFromWkt(std::string path) override;
  std::string ToString() const override;

  // Force rings to be closed.
  // If this geometry, or any contained geometries has polygon rings that are not closed,
  // they will be closed by adding the starting point at the end.
  void CloseRings();

  // Get the area of the closed ring.
  double GetArea() const;

  bool Contains(const OGRGeometry *) const;

 protected:
  bool Contains(const OGRPoint *) const;
};

#endif //OGR_OGRLINEARRING_H
