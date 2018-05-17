// Convex - Assignment 5 for course Programming Language
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

#include <cmath>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

#include "io_util.hpp"
#include "line.h"
#include "point.h"

constexpr const double EPS = 1e-9;
constexpr const int INF = 2147483647;

typedef std::vector<int> Path;

// Comparing whether two path are the same.
struct PathComparator {
  bool operator()(const Path &lhs, const Path &rhs) const {
    if (lhs.size() != rhs.size()) return lhs.size() < rhs.size();
    else {
      std::vector<int> lhs_copy;
      std::vector<int> rhs_copy;
      for (int i = 0; i < lhs.size(); ++i) {
        lhs_copy.push_back(lhs[i] >= 0 ? lhs[i] : ~lhs[i]);
        rhs_copy.push_back(rhs[i] >= 0 ? rhs[i] : ~rhs[i]);
      }

      std::sort(lhs_copy.begin(), lhs_copy.end());
      std::sort(rhs_copy.begin(), rhs_copy.end());

      for (int i = 0; i < lhs_copy.size(); ++i) {
        if (lhs_copy[i] != rhs_copy[i]) return lhs_copy[i] < rhs_copy[i];
      }

      return false;
    }
  }
};

typedef std::set<Path, PathComparator> PathSet;

typedef std::vector<luolc::graphics::Point> Points;

typedef std::vector<luolc::graphics::Line> Lines;

// Solves the whole problem.
void Solve(FILE *fp);

// Depth-First Search for polygons.
PathSet SearchPolygon(Path path, Lines lines);

// Gets the vertices sequence of a polygon represented as a path, anticlockwise.
Points Vertices(Path path, Lines lines);

// Gets the directed area of a polygon represented as a path.
double Area(Path path, Lines lines);

// Gets the rectangle hull of the polygon represented as a path.
Points RectangleHull(Path path, Lines lines);

// Checks whether the polygon is convex.
bool IsConvex(Path path, Lines lines);

// Checks whether a point is in polygon.
bool IsPointInPolygon(luolc::graphics::Point point, Path path, Lines lines);

// The executable entrance.
int main() {
  constexpr const char *input_path = "input.txt";

  if (!IsFileExists(input_path)) {
    Println("输入文件不存在");
    return 0;
  }

  FILE *fp = std::fopen(input_path, "r");

  try {
    Solve(fp);
  } catch (std::exception &ex) {
    Println("发生未知错误:", ex.what());
    fclose(fp);
  }

  return 0;
}

void Solve(FILE *fp) {
  // coordinates of the first point
  double x1;
  double y1;

  // coordinates of the second point
  double x2;
  double y2;

  Lines lines;

  while (true) {
    auto n_args = fscanf(fp, "%lf %lf\t%lf %lf", &x1, &y1, &x2, &y2);

    if (n_args == EOF)
      break;
    else if (n_args != 4) {
      Println("输入格式错误");
      return;
    } else {
      lines.push_back(luolc::graphics::Line({x1, y1}, {x2, y2}));
    }
  }

  PathSet path_set;
  for (int i = 0; i < lines.size(); ++i) {
    auto branch_result = SearchPolygon(Path(1, i), lines);
    path_set.insert(branch_result.begin(), branch_result.end());
  }

  std::vector<Path> answer;
  answer.insert(answer.end(), path_set.begin(), path_set.end());
  auto n_convex = std::count_if(answer.begin(),
                                answer.end(),
                                [lines](Path path) { return IsConvex(path, lines); });
  Println("存在", answer.size(), "个多边形（其中有", n_convex, "个凸多边形）:");

  int index = 0;
  for (const auto &path: answer) {
    ++index;
    Println("[", index, "]", IsConvex(path, lines) ? "凸" : "非凸");

    Print("顶点: ");
    for (const auto &p: Vertices(path, lines)) {
      Print("(");
      Print(p.x);
      Print(",");
      Print(p.y);
      Print(") ");
    }
    Println();

    Println("面积:", abs(Area(path, lines)));

    auto rectangle = RectangleHull(path, lines);
    Print("外包矩形: 以 ");
    Print("(");
    Print(rectangle[0].x);
    Print(",");
    Print(rectangle[0].y);
    Print(") (");
    Print(rectangle[1].x);
    Print(",");
    Print(rectangle[1].y);
    Println(") 为对角线");
    Println();
  }

  if (answer.size() > 0) {
    Print("请输入需判断的点坐标: ");
    if (scanf("%lf %lf", &x1, &y1) != 2) {
      Println("输入格式错误");
    } else {
      auto point = luolc::graphics::Point(x1, y1);
      auto n_inside = std::count_if(
          answer.begin(),
          answer.end(),
          [point, lines](Path path) { return IsPointInPolygon(point, path, lines); });

      Println("输入点在", n_inside, "个多边形内，编号为:");

      for (int i = 0; i < answer.size(); ++i) {
        auto path = answer[i];
        if (IsPointInPolygon(point, path, lines)) {
          Println("[", i + 1, "]");
        }
      }
    }
  }
}

PathSet SearchPolygon(Path path, Lines lines) {
  PathSet result;

  auto last_index = path.back() >= 0 ? path.back() : ~path.back();
  auto last_line = lines[last_index];
  auto last_point = path.back() >= 0 ? last_line.Vertex2() : last_line.Vertex1();

  for (int i = 0; i < lines.size(); ++i) {
    if (i == last_index) continue;

    auto directed_i = INF;

    if (lines[i].Vertex1().IsCloseTo(last_point)) {
      directed_i = i;
    } else if (lines[i].Vertex2().IsCloseTo(last_point)) {
      directed_i = ~i;
    }

    // the current line is linked to the last line in the path
    if (directed_i != INF) {
      if (directed_i == path.front() && path.size() > 2) {
        // find a polygon now
        result.insert(Path(path));
      } else if (std::find(path.begin(), path.end(), i) == path.end()
          && std::find(path.begin(), path.end(), ~i) == path.end()) {
        // the current line is not in the path, search deeper
        path.push_back(directed_i);
        auto branch_result = SearchPolygon(path, lines);
        result.insert(branch_result.begin(), branch_result.end());
        path.pop_back();
      }
    }
  }

  return result;
}

double Area(Path path, Lines lines) {
  Points points;

  for (const auto &directed_i: path) {
    auto index = directed_i >= 0 ? directed_i : ~directed_i;
    auto line = lines[index];
    points.push_back(directed_i >= 0 ? line.Vertex1() : line.Vertex2());
  }

  points.push_back(lines[path.front()].Vertex1());

  double result = 0;

  for (int i = 0; i < points.size() - 1; ++i) {
    result += points[i].x * points[i + 1].y - points[i].y * points[i + 1].x;
  }

  return result / 2;
}

Points Vertices(Path path, Lines lines) {
  Points points;

  for (const auto &directed_i: path) {
    auto index = directed_i >= 0 ? directed_i : ~directed_i;
    auto line = lines[index];
    points.push_back(directed_i >= 0 ? line.Vertex1() : line.Vertex2());
  }

  if (Area(path, lines) < 0) std::reverse(points.begin(), points.end());

  return points;
}

Points RectangleHull(Path path, Lines lines) {
  auto points = Vertices(path, lines);

  double max_x = -INF;
  double max_y = -INF;
  double min_x = INF;
  double min_y = INF;

  for (const auto &p: points) {
    if (max_x < p.x) max_x = p.x;
    if (max_y < p.y) max_y = p.y;
    if (min_x > p.x) min_x = p.x;
    if (min_y > p.y) min_y = p.y;
  }

  auto rectangle = Points();
  rectangle.emplace_back(min_x, min_y);
  rectangle.emplace_back(max_x, max_y);

  return rectangle;
}

bool IsConvex(Path path, Lines lines) {
  Points vectors;

  for (const auto &directed_i: path) {
    auto index = directed_i >= 0 ? directed_i : ~directed_i;
    auto line = lines[index];
    vectors.push_back(directed_i >= 0 ? line.Vector() : -line.Vector());
  }

  vectors.push_back(lines[path.front()].Vector());

  // clockwise -> anticlockwise
  if (Area(path, lines) < 0) {
    std::reverse(vectors.begin(), vectors.end());
    for (int i = 0; i < vectors.size(); ++i) vectors[i] = -vectors[i];
  }

  for (int i = 0; i < vectors.size() - 1; ++i) {
    if (vectors[i].Det(vectors[i + 1]) < -EPS) return false;
  }

  return true;
}

bool IsPointInPolygon(luolc::graphics::Point point, Path path, Lines lines) {
  auto x = point.x;
  auto y = point.y;

  bool odd_node = false;
  auto vertices = Vertices(path, lines);
  auto length = static_cast<int>(vertices.size());

  for (int i = 0, j = length - 1; i < length; ++i) {
    if ((vertices[i].y < y && vertices[j].y >= y || vertices[j].y < y && vertices[i].y >= y)
        && (vertices[i].x <= x || vertices[j].x <= x)) {
      odd_node ^= (vertices[i].x
          + (y - vertices[i].y) / (vertices[j].y - vertices[i].y) * (vertices[j].x - vertices[i].x)
          < x);
    }
    j = i;
  }

  return odd_node;
}
