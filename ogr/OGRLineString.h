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

#ifndef OGR_OGRLINESTRING_H
#define OGR_OGRLINESTRING_H

#include "OGRSimpleCurve.h"

// Defined in this file.
class OGRLineString;

// Concrete representation of a multi-vertex line.
class OGRLineString : public OGRSimpleCurve {
 public:
  OGRLineString();
  OGRLineString(const OGRLineString &);
  ~OGRLineString();

  const char *GetGeometryType() const override;
  OGREnvelope GetMBR() const override;
  void Copy(const OGRGeometry &) override;
  OGRGeometry *Clone() const override;
  bool Equals(const OGRLineString &) const;
  bool Equals(const OGRGeometry *) const override;
  void ImportFromWkt(std::string path) override;
  std::string ToString() const override;

  double GetLength() const override;
};

#endif //OGR_OGRLINESTRING_H
