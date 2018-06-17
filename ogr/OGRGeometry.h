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

#ifndef OGR_OGRGEOMETRY_H
#define OGR_OGRGEOMETRY_H

#include <string>

#include "OGREnvelope.h"

// Defined in this file.
class OGRGeometry;

// Abstract base class for all geometry classes.
class OGRGeometry {
 public:
  constexpr static const double EPS = 1e-9;

  OGRGeometry();
  virtual ~OGRGeometry();

  // Gets the unique id of this geometry.
  int GetID() const;

  // Fetch geometry type.
  virtual const char *GetGeometryType() const = 0;

  // Computes and returns the bounding envelope for this geometry.
  virtual OGREnvelope GetMBR() const = 0;

  // Copies.
  virtual void Copy(const OGRGeometry &) = 0;

  // Makes a copy of this object.
  virtual OGRGeometry *Clone() const = 0;

  // Returns true if two geometries are equivalent.
  bool Equals(const OGRGeometry &) const;
  virtual bool Equals(const OGRGeometry *) const = 0;

  // Assigns geometry from well known text data.
  virtual void ImportFromWkt(std::string path) = 0;

  // Converts a geometry into well known text format.
  void ExportToWkt(std::string path);

  // Gets the string representation of the geometry.
  virtual std::string ToString() const;

 protected:
  static int incremental_index;

  static bool IsClose(double, double);

  bool TypeEquals(const OGRGeometry *) const;

 private:
  int id_;
};

#endif //OGR_OGRGEOMETRY_H
