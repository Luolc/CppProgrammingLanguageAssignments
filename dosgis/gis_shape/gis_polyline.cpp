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
// The class to represent a DOS-GIS polyline shape.

#include "gis_polyline.h"

#include <sstream>
#include <utility>
#include "../util/string_util.hpp"

//
#include <iostream>

namespace luolc {
namespace dosgis {

GisPolyline::GisPolyline() = default;

GisPolyline::GisPolyline(const Args &args) {
  Reset(args);
}

void GisPolyline::Reset(const Args &args) {
  auto args_obj = ParseArgs(args);
  vertices_ = args_obj.second;
}

void GisPolyline::Update(const Args &args) {
  auto args_obj = ParseArgs(args);
  auto index = args_obj.first;
  auto point = args_obj.second.front();
  vertices_[index] = point;
}

void GisPolyline::Move(const Args &args) {
  auto args_obj = ParseArgs(args);
  auto index = args_obj.first;
  auto point = args_obj.second.front();
  vertices_[index].x += point.x;
  vertices_[index].y += point.y;
}

void GisPolyline::Remove(const Args &args) {
  auto index = std::stoi(args.front());
  vertices_.erase(vertices_.begin() + index);
}

const std::string GisPolyline::ToString() const {
  std::ostringstream oss;

  oss << "polyline " << id_ << " [";
  for (int i = 0; i < vertices_.size(); ++i) {
    oss << "[" << vertices_[i].x << "," << vertices_[i].y << "]";
    if (i != vertices_.size() - 1) oss << ", ";
  }
  oss << "], name=" << name_ << ", length=" << length_;

  return oss.str();
}

const std::pair<int, std::vector<graphics::Point>> GisPolyline::ParseArgs(const Args &args) const {
  auto index = args.size() > 1 ? std::stoi(args.front()) : 0;

  std::vector<graphics::Point> points;
  auto coordinates = Split(args.back(), ',');
  for (int i = 0; i < coordinates.size(); i += 2) {
    auto x = std::stod(coordinates[i]);
    auto y = std::stod(coordinates[i + 1]);
    points.emplace_back(x, y);
  }

  return {index, points};
}

} // namespace dosgis
} // namespace luolc
