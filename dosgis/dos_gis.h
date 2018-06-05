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
// The general DOS-GIS manager to perform operations.

#ifndef DOSGIS_DOS_GIS_H
#define DOSGIS_DOS_GIS_H

#include <functional>
#include <string>
#include <unordered_map>

#include "gis_shape/abstract_gis_shape.h"
#include "gis_shape/gis_point.h"
#include "gis_shape/gis_polygon.h"
#include "gis_shape/gis_polyline.h"
#include "gis_shape/gis_ring.h"
#include "gis_shape/gis_shape_set.h"
#include "util/string_util.hpp"

namespace luolc {
namespace dosgis {

// Represents an operation command.
struct Command {
  typedef AbstractGisShape::Args Args;

  // Operations: add, del, set, judge
  std::string operation;

  // ShapeTypes: point, polyline, ring, polygon
  std::string shape_type;

  // The id of the subject.
  std::string subject_id;

  // The arguments of the command.
  Args args;

  // Constructs a Command with the raw text format.
  explicit Command(const std::string &cmd) {
    auto items = Split(cmd, ' ');
    operation = items[0];
    shape_type = items[1];
    subject_id = items[2];
    args = Args(items.begin() + 3, items.end());
  }
};

// Defined in this file.
class DosGisManager;

// The general DOS-GIS manager to perform operations.
class DosGisManager {
 public:
  typedef AbstractGisShape::Args Args;

  // Constructs a DosGisManager.
  DosGisManager();

  // Executes a command (represented as plain text).
  void Execute(const std::string &cmd_line);

  void PrintAllShapes() const;

 private:
  GisShapeSet<GisPoint> point_set_;
  GisShapeSet<GisPolyline> polyline_set_;
  GisShapeSet<GisRing> ring_set_;
  GisShapeSet<GisPolygon> polygon_set_;
  std::unordered_map<std::string, AbstractGisShapeSet *> sets_;

  // operation -> operation_function(cmd)
  std::unordered_map<std::string, std::function<void(const Command &)>> operation_fn_;

  // shape_type -> judge_function(subject_id, object_id)
  std::unordered_map<std::string,
                     std::function<bool(const std::string &, const std::string &)>> judge_fn_;

  // update_operation -> update_function(cmd, update_args)
  std::unordered_map<std::string,
                     std::function<void(const Command &, const Args &)>> update_fn_;

  // Initializes operation function maps.
  void InitOperationFnMap();
  void InitJudgeFnMap();
  void InitUpdateFnMap();
};

} // namespace dosgis
} // namespace luolc

#endif //DOSGIS_DOS_GIS_H
