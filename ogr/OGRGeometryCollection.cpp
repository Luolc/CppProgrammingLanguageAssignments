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

#include "OGRGeometryCollection.h"

#include <sstream>
#include <stdexcept>
#include <cstring>

OGRGeometryCollection::OGRGeometryCollection() = default;

OGRGeometryCollection::OGRGeometryCollection(const OGRGeometryCollection &other) {
  for (auto i = other.begin(); i != other.end(); ++i) {
    container_.push_back((*i)->Clone());
  }
}

OGRGeometryCollection::~OGRGeometryCollection() {
  for (auto i = 0; i < container_.size(); ++i) delete container_[i];
  container_.clear();
}

const char *OGRGeometryCollection::GetGeometryType() const {
  return "OGRGeometryCollection";
}

OGREnvelope OGRGeometryCollection::GetMBR() const {
  auto result = OGREnvelope();

  for (const auto &i : container_) {
    result.Merge(i->GetMBR());
  }

  return result;
}

void OGRGeometryCollection::Copy(const OGRGeometry &other) {
  auto p = (OGRGeometryCollection *) other.Clone();
  *this = *p;
}

OGRGeometry *OGRGeometryCollection::Clone() const {
  return new OGRGeometryCollection(*this);
}

bool OGRGeometryCollection::Equals(const OGRGeometryCollection &other) const {
  return Equals(&other);
}

bool OGRGeometryCollection::Equals(const OGRGeometry *other) const {
  if (!TypeEquals(other)) return false;

  auto p = (OGRGeometryCollection *) other;
  for (auto i = begin(), j = p->begin(); i != end() || j != p->end(); ++i, ++j) {
    if (i == end() ^ j == p->end()) return false;
    if (!(*i)->Equals(*j)) return false;
  }

  return true;
}

void OGRGeometryCollection::ImportFromWkt(std::string path) {
}

std::string OGRGeometryCollection::ToString() const {
  std::ostringstream oss;

  oss << "OGRGeometryCollection (";
  for (auto i = begin(); i != end(); ++i) {
    if (i != begin()) oss << ", ";
    oss << (*i)->ToString();
  }
  oss << ")";

  return oss.str();
}

OGRGeometryCollection::const_iterator OGRGeometryCollection::begin() const {
  return container_.begin();
}

OGRGeometryCollection::const_iterator OGRGeometryCollection::end() const {
  return container_.end();
}

void OGRGeometryCollection::AddGeometry(const OGRGeometry *item) {
  CheckItemType(item);

  container_.push_back(item->Clone());
}

void OGRGeometryCollection::RemoveGeometry(int index) {
  auto position = begin() + index;
  auto ptr = *position;
  container_.erase(position);
  delete ptr;
}

const OGRGeometry *OGRGeometryCollection::GetGeometry(int index) const {
  return *(begin() + index);
}

void OGRGeometryCollection::UpdateGeometry(int index, const OGRGeometry *item) {
  CheckItemType(item);

  auto ptr = *(begin() + index);
  container_[index] = item->Clone();
  delete ptr;
}

int OGRGeometryCollection::GetNumGeometries() const {
  return static_cast<int>(container_.size());
}

void OGRGeometryCollection::CheckItemType(const OGRGeometry *item) const {
  if (strcmp(ItemType(), "OGRGeometry") == 0) return;

  if (strcmp(ItemType(), item->GetGeometryType()) != 0) {
    std::ostringstream oss;
    oss << "Item type mismatch. Expect " << ItemType()
        << ", but received " << item->GetGeometryType() << ".";
    throw std::invalid_argument(oss.str());
  }
}

const char *OGRGeometryCollection::ItemType() const {
  return "OGRGeometry";
}
