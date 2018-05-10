// Polyline - Assignment 4 for course Programming Language
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
// The executable entrance of the project.

#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>

#include "io_util.hpp"
#include "line.h"
#include "point.h"
#include "polyline.h"

// Prints the error message with line number.
inline void PrintErrorMessage(const char *message, int line_number) {
  Println("[Error]", message, "建议检查第", line_number, "行");
}

// Checks if the file content is missing and prints the error message if encountering error.
inline bool CheckInputLength(int line_number, int file_length) {
  if (line_number > file_length) {
    Print("[Error] 文件缺失，输入长度与预期不符");
    return false;
  }
  return true;
}

// The executable entrance.
int main() {
  freopen("input.txt", "r", stdin);

  auto input_file_length = (int) GetFileLines("input.txt").size();
  int line_number = 1; // denotes the current line number
  if (!CheckInputLength(line_number, input_file_length)) return 0;

  int n_case;
  if (scanf("%d", &n_case) < 1) {
    PrintErrorMessage("测试用例数格式错误", line_number);
    return 0;
  }

  for (int c = 0; c < n_case; ++c) {
    if (!CheckInputLength(++line_number, input_file_length)) return 0;
    int n_vertex;
    int n_mark;
    if (scanf("%d %d", &n_vertex, &n_mark) < 2) {
      PrintErrorMessage("测试用例元数据（顶点数，标记点数）格式错误", line_number);
      return 0;
    }

    auto vertices = std::vector<luolc::graphics::Point>();

    for (int i = 0; i < n_vertex; ++i) {
      if (!CheckInputLength(++line_number, input_file_length)) return 0;
      double x;
      double y;
      if (scanf("%lf %lf", &x, &y) < 2) {
        PrintErrorMessage("测试用例顶点数据格式错误", line_number);
        return 0;
      }
      vertices.emplace_back(x, y);
    }

    auto polyline = luolc::graphics::Polyline(vertices);

    auto length = polyline.Length();
    auto line_count = polyline.Count();
    auto k_dividing_points = polyline.GetKDividingPoints(n_mark + 1);

    Println("[ Polyline", c + 1, "]");
    Println("总长度:", length);
    Println("线段数量:", line_count);
    Println("注记:");
    for (const auto &p: k_dividing_points) {
      constexpr double width = 20; // width of the mark
      constexpr double height = 10; // height of the mark
      constexpr double eps = 1e-9;
      auto x = p.x + eps;
      auto y = p.y - eps; // move a minor distance along bottom right direction (for smoothing)

      // vertices of the mark rectangle
      auto top_left = luolc::graphics::Point(x, y);
      auto top_right = luolc::graphics::Point(x + width, y);
      auto bottom_left = luolc::graphics::Point(x, y - height);
      auto bottom_right = luolc::graphics::Point(x + width, y - height);

      auto mark_rect = std::vector<luolc::graphics::Line>();
      mark_rect.emplace_back(top_left, top_right);
      mark_rect.emplace_back(top_right, bottom_right);
      mark_rect.emplace_back(bottom_right, bottom_left);
      mark_rect.emplace_back(bottom_left, top_left);

      // the mark intersects the polyline if and only if any of the rectangle edges intersects
      // the polyline
      auto intersect = std::any_of(
          mark_rect.begin(),
          mark_rect.end(),
          [&polyline](const luolc::graphics::Line &l) { return polyline.Intersect(l); });

      Println(p.x, p.y, intersect ? "相交" : "不相交");
    }
    Println();
  }

  return 0;
}
