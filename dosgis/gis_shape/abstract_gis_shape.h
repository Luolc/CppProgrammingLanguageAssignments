// DOS-GIS - Assignment 6 for course Programming Language
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
// The base class of a DOS-GIS shape.

#ifndef DOSGIS_ABSTRACT_SHAPE_H
#define DOSGIS_ABSTRACT_SHAPE_H

#include <string>
#include <vector>

#include "../graphics/point.h"

namespace luolc {
namespace dosgis {

// Defined in this file.
class AbstractGisShape;

// Defined in this file.
class AbstractGisVertices;

// The base class of a DOS-GIS shape.
class AbstractGisShape {
 public:
  typedef std::vector<std::string> Args;

  // Initializes the fields.
  AbstractGisShape();

  // Comparision operators.
  const bool operator<(const AbstractGisShape &) const;

  // Gets the string representation of this shape. Just like the Java-style method.
  virtual const std::string ToString() const = 0;

  // Operations.
  void SetId(std::string id);
  void SetName(std::string name);
  virtual void Update(const Args &args) = 0;
  virtual void Move(const Args &args) = 0;

 protected:
  static constexpr const char *NULL_VAL = "NULL";
  std::string id_;
  std::string name_;
};

// The base class of a DOS-GIS shape with several vertices.
class AbstractGisVertices : public AbstractGisShape {
 public:
  // Initializes the fields.
  AbstractGisVertices();

  // Operations
  void SetLength(std::string length);
  void SetArea(std::string area);
  virtual void Remove(const Args &args) = 0;

 protected:
  std::string length_;
  std::string area_;
};

} // namespace dosgis
} // namespace luolc

#endif //DOSGIS_ABSTRACT_SHAPE_H
