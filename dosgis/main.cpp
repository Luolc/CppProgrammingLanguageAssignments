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
// The executable entrance of the project.

#include <cstdio>

#include "dos_gis.h"

int main() {
  /**
   * You can uncomment one of the lines below to choose a file as the input, including:
   *  - "input.txt":
   *      the sample input provided on course.pku.edu.cn
   *
   *  - "input_extend.txt":
   *      a more completely test case which covers all valid commands
   *
   *  - "input_error.txt":
   *      an example to show the error handling
   */
  constexpr const char *input_fp = "input.txt";
//  constexpr const char *input_fp = "input_extend.txt";
//  constexpr const char *input_fp = "input_error.txt";

  freopen(input_fp, "r", stdin);
  freopen("output.txt", "w", stdout);

  luolc::dosgis::DosGisManager manager;

  std::string cmd;
  while (std::getline(std::cin, cmd)) {
    if (cmd.empty()) continue;
    manager.Execute(cmd);
  }

  manager.PrintAllShapes();

  return 0;
}
