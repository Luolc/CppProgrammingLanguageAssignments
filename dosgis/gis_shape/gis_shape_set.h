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
// The container to store DOS-GIS shape.

#pragma clang diagnostic push
#pragma ide diagnostic ignored "HidingNonVirtualFunction"

#ifndef DOSGIS_GIS_SHAPE_SET_H
#define DOSGIS_GIS_SHAPE_SET_H

#include <set>
#include <string>
#include <utility>
#include <vector>

#include "abstract_gis_shape.h"
#include "gis_polyline.h"
#include "../util/io_util.hpp"

namespace luolc {
namespace dosgis {

// Defined in this file.
class AbstractGisShapeSet;

// Defined in this file.
template<typename T>
class GisShapeSet;

// The abstract class of GisShapeSet which defines several common operations.
class AbstractGisShapeSet {
 public:
  typedef AbstractGisShape::Args Args;

  // Modifiers
  virtual void Insert(std::string id, const Args &args) = 0;
  virtual void Erase(std::string id) = 0;
  virtual void Update(std::string id, const Args &args) = 0;
  virtual void Move(std::string id, const Args &args) = 0;
  virtual void SetName(std::string id, std::string name) = 0;
  virtual void SetLength(std::string id, std::string length) = 0;
  virtual void SetArea(std::string id, std::string area) = 0;
  virtual void RemovePoint(std::string id, const Args &args) = 0;

  // Operations
  template<typename R>
  R *Find(std::string id) {
    auto it = ((GisShapeSet<R> *) this)->Find(id);
    return ((R *) &(*it));
  }
  virtual bool Contain(std::string id) const = 0;

  // Prints all the shapes in alphabetic order.
  virtual void PrintAllShapes() const = 0;
};

// The container to store DOS-GIS shape.
template<typename T>
class GisShapeSet : public AbstractGisShapeSet {
 public:
  typedef AbstractGisShape::Args Args;

  typedef T value_type;
  typedef typename std::set<value_type>::iterator iterator;
  typedef typename std::set<value_type>::const_iterator const_iterator;
  typedef AbstractGisShape *base_pointer;
  typedef AbstractGisVertices *vertices_pointer;

  // Modifiers
  void Insert(std::string id, const Args &args) override;
  void Erase(std::string id) override;
  void Update(std::string id, const Args &args) override;
  void Move(std::string id, const Args &args) override;
  void SetName(std::string id, std::string name) override;
  void SetLength(std::string id, std::string length) override;
  void SetArea(std::string id, std::string area) override;
  void RemovePoint(std::string id, const Args &args) override;

  // Operations
  iterator Find(std::string id);
  const_iterator Find(std::string id) const;
  bool Contain(std::string id) const override;

  void PrintAllShapes() const override;

 private:
  std::set<value_type> set_;
};

template<typename T>
void GisShapeSet<T>::Insert(std::string id, const Args &args) {
  auto shape = value_type(args);
  ((base_pointer) &shape)->SetId(std::move(id));
  set_.insert(shape);
}

template<typename T>
void GisShapeSet<T>::Erase(std::string id) {
  set_.erase(Find(id));
}

template<typename T>
void GisShapeSet<T>::Update(std::string id, const GisShapeSet::Args &args) {
  ((base_pointer) &(*Find(id)))->Update(args);
}

template<typename T>
void GisShapeSet<T>::Move(std::string id, const GisShapeSet::Args &args) {
  ((base_pointer) &(*Find(id)))->Move(args);
}

template<typename T>
void GisShapeSet<T>::SetName(std::string id, std::string name) {
  ((base_pointer) &(*Find(id)))->SetName(name);
}

template<typename T>
void GisShapeSet<T>::SetLength(std::string id, std::string length) {
  ((vertices_pointer) &(*Find(id)))->SetLength(length);
}

template<typename T>
void GisShapeSet<T>::SetArea(std::string id, std::string area) {
  ((vertices_pointer) &(*Find(id)))->SetArea(area);
}

template<typename T>
void GisShapeSet<T>::RemovePoint(std::string id, const GisShapeSet::Args &args) {
  ((vertices_pointer) &(*Find(id)))->Remove(args);
}

template<typename T>
typename GisShapeSet<T>::iterator GisShapeSet<T>::Find(std::string id) {
  auto fake_val = value_type();
  ((base_pointer) &fake_val)->SetId(std::move(id));
  return set_.find(fake_val);
}

template<typename T>
typename GisShapeSet<T>::const_iterator GisShapeSet<T>::Find(std::string id) const {
  auto fake_val = value_type();
  ((base_pointer) &fake_val)->SetId(std::move(id));
  return set_.find(fake_val);
}

template<typename T>
bool GisShapeSet<T>::Contain(std::string id) const {
  return Find(id) != set_.end();
}

template<typename T>
void GisShapeSet<T>::PrintAllShapes() const {
  for (auto it = set_.begin(); it != set_.end(); ++it) {
    Println(((base_pointer) &(*it))->ToString());
  }
}

} // namespace dosgis
} // namespace luolc

#endif //DOSGIS_GIS_SHAPE_SET_H

#pragma clang diagnostic pop
