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

#ifndef OGR_OGRMULTIPOINT_H
#define OGR_OGRMULTIPOINT_H

#include "OGRGeometryCollection.h"

// Defined in this file.
class OGRMultiPoint;

// A collection of OGRPoint.
class OGRMultiPoint : public OGRGeometryCollection {
 public:
  OGRMultiPoint();
  OGRMultiPoint(const OGRMultiPoint &);

  const char *GetGeometryType() const override;
  void Copy(const OGRGeometry &) override;
  OGRGeometry *Clone() const override;
  bool Equals(const OGRMultiPoint &) const;
  void ImportFromWkt(std::string path) override;
  std::string ToString() const override;

 protected:
  const char *ItemType() const override;
};

#endif //OGR_OGRMULTIPOINT_H
