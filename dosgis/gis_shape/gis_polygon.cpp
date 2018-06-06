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
// The class to represent a DOS-GIS polygon shape.

#include "gis_polygon.h"

#include <sstream>

#include "../util/string_util.hpp"

namespace luolc {
namespace dosgis {

GisPolygon::GisPolygon() {
  inner_ = new GisRing();
  outer_ = new GisRing();
  rings_["inner"] = inner_;
  rings_["outer"] = outer_;
};

GisPolygon::GisPolygon(const Args &args) {
  inner_ = new GisRing();
  outer_ = new GisRing();
  rings_["inner"] = inner_;
  rings_["outer"] = outer_;

  auto args_obj = ParseArgs(args);
  rings_[args_obj.first]->Reset(args_obj.second);
}

void GisPolygon::Update(const Args &args) {
  auto args_obj = ParseArgs(args);
  rings_[args_obj.first]->Update(args_obj.second);
}

void GisPolygon::Move(const Args &args) {
  auto args_obj = ParseArgs(args);
  rings_[args_obj.first]->Move(args_obj.second);
}

void GisPolygon::Remove(const Args &args) {
  auto args_obj = ParseArgs(args);
  rings_[args_obj.first]->Remove(args_obj.second);
}

void GisPolygon::Reset(const std::string &which, const Args &args) {
  rings_[which]->Reset(args);
}

const std::string GisPolygon::ToString() const {
  std::ostringstream oss;

  oss << "polygon " << id_ << " outer=" << outer_->VerticesString()
      << ", inner=" << inner_->VerticesString()
      << ", name=" << name_ << ", length=" << length_ << ", area=" << area_;

  return oss.str();
}

bool GisPolygon::IsCover(const GisPoint &point) const {
  return outer_->IsCover(point) && !inner_->IsCover(point);
}

const std::pair<std::string, AbstractGisShape::Args> GisPolygon::ParseArgs(const Args &args) const {
  std::string which;
  Args ring_args;

  if (args.size() > 1) {
    which = args.front();
    ring_args = Args(args.begin() + 1, args.end());
  } else {
    ring_args = Args(args.begin(), args.end());
  }

  return {which, ring_args};
}

} // namespace dosgis
} // namespace luolc
