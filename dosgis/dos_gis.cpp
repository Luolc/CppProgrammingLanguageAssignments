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

#include "dos_gis.h"

#include "util/string_util.hpp"
#include "util/io_util.hpp"

namespace luolc {
namespace dosgis {

DosGisManager::DosGisManager() {
  sets_["point"] = &point_set_;
  sets_["polyline"] = &polyline_set_;
  sets_["ring"] = &ring_set_;
  sets_["polygon"] = &polygon_set_;

  InitOperationFnMap();
  InitUpdateFnMap();
  InitJudgeFnMap();
}

void DosGisManager::InitOperationFnMap() {
  operation_fn_["add"] = [this](const Command &cmd) {
    sets_[cmd.shape_type]->Insert(cmd.subject_id, cmd.args);
  };
  operation_fn_["del"] = [this](const Command &cmd) {
    sets_[cmd.shape_type]->Erase(cmd.subject_id);
  };
  operation_fn_["set"] = [this](const Command &cmd) {
    auto update_op = cmd.args.front();
    auto update_args = Args(cmd.args.begin() + 1, cmd.args.end());
    update_fn_[update_op](cmd, update_args);
  };
  operation_fn_["judge"] = [this](const Command &cmd) {
    auto object_id = cmd.args.back();
    auto result = judge_fn_[cmd.shape_type](cmd.subject_id, object_id);
    Println(result ? "True" : "False");
  };
}

void DosGisManager::InitUpdateFnMap() {
  update_fn_["set"] = [this](const Command &cmd, const Args &args) {
    sets_[cmd.shape_type]->Update(cmd.subject_id, args);
  };
  update_fn_["move"] = [this](const Command &cmd, const Args &args) {
    sets_[cmd.shape_type]->Move(cmd.subject_id, args);
  };
  update_fn_["del"] = [this](const Command &cmd, const Args &args) {
    sets_[cmd.shape_type]->RemovePoint(cmd.subject_id, args);
  };
  update_fn_["name"] = [this](const Command &cmd, const Args &args) {
    sets_[cmd.shape_type]->SetName(cmd.subject_id, args.front());
  };
  update_fn_["set_length"] = [this](const Command &cmd, const Args &args) {
    sets_[cmd.shape_type]->SetLength(cmd.subject_id, args.front());
  };
  update_fn_["set_area"] = [this](const Command &cmd, const Args &args) {
    sets_[cmd.shape_type]->SetArea(cmd.subject_id, args.front());
  };
  update_fn_["inner"] = [this](const Command &cmd, const Args &args) {
    sets_["polygon"]->Find<GisPolygon>(cmd.subject_id)->Reset("inner", args);
  };
  update_fn_["outer"] = [this](const Command &cmd, const Args &args) {
    sets_["polygon"]->Find<GisPolygon>(cmd.subject_id)->Reset("outer", args);
  };
}

void DosGisManager::InitJudgeFnMap() {
  judge_fn_["point"] = [this](const std::string &subject_id, const std::string &object_id) {
    auto subject = sets_["point"]->Find<GisPoint>(subject_id);
    auto object = sets_["point"]->Find<GisPoint>(object_id);
    return subject->IsCloseTo(*object);
  };
  judge_fn_["ring"] = [this](const std::string &subject_id, const std::string &object_id) {
    auto subject = sets_["ring"]->Find<GisRing>(subject_id);
    auto object = sets_["point"]->Find<GisPoint>(object_id);
    return subject->IsCover(*object);
  };
  judge_fn_["polygon"] = [this](const std::string &subject_id, const std::string &object_id) {
    auto subject = sets_["polygon"]->Find<GisPolygon>(subject_id);
    auto object = sets_["point"]->Find<GisPoint>(object_id);
    return subject->IsCover(*object);
  };
}

void DosGisManager::Execute(const std::string &cmd_line) {
  auto cmd = Command(cmd_line);
  operation_fn_[cmd.operation](cmd);
}

void DosGisManager::PrintAllShapes() const {
  point_set_.PrintAllShapes();
  polyline_set_.PrintAllShapes();
  ring_set_.PrintAllShapes();
  polygon_set_.PrintAllShapes();
}

} // namespace dosgis
} // namespace luolc
