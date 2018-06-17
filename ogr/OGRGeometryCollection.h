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
// A collection of 1 or more geometry objects.

#ifndef OGR_OGRGEOMETRYCOLLECTION_H
#define OGR_OGRGEOMETRYCOLLECTION_H

#include "OGRGeometry.h"

#include <vector>

// Defined in this file.
class OGRGeometryCollection;

// A collection of 1 or more geometry objects.
class OGRGeometryCollection : public OGRGeometry {
 public:
  typedef std::vector<OGRGeometry *>::const_iterator const_iterator;

  OGRGeometryCollection();
  OGRGeometryCollection(const OGRGeometryCollection &);
  ~OGRGeometryCollection();

  const char *GetGeometryType() const override;
  OGREnvelope GetMBR() const override;
  void Copy(const OGRGeometry &) override;
  OGRGeometry *Clone() const override;
  bool Equals(const OGRGeometryCollection &) const;
  bool Equals(const OGRGeometry *) const override;
  void ImportFromWkt(std::string path) override;
  std::string ToString() const override;

  const_iterator begin() const;
  const_iterator end() const;

  // Adds a geometry to the container.
  // Some subclasses of OGRGeometryCollection restrict the types of geometry that can be added,
  // and may throw an error. The passed geometry is cloned to make an internal copy.
  void AddGeometry(const OGRGeometry *);

  // Removes a geometry from the container.
  // Removing a geometry will cause the geometry count to drop by one,
  // and all "higher" geometries will shuffle down one in index.
  void RemoveGeometry(int index);

  // Fetches geometry from container.
  // This method returns a pointer to a geometry within the container.
  // The returned geometry remains owned by the container, and should not be modified.
  // The pointer is only valid until the next change to the geometry container.
  // Use OGRGeometry::clone() to make a copy.
  const OGRGeometry *GetGeometry(int index) const;

  // Updates the geometry at given position.
  // Some subclasses of OGRGeometryCollection restrict the types of geometry that can be updated,
  // and may throw an error. The passed geometry is cloned to make an internal copy.
  void UpdateGeometry(int index, const OGRGeometry *);

  // Gets the number of geometries in the container.
  int GetNumGeometries() const;

 protected:
  std::vector<OGRGeometry *> container_;

  void CheckItemType(const OGRGeometry *) const;

  virtual const char *ItemType() const;
};

#endif //OGR_OGRGEOMETRYCOLLECTION_H
