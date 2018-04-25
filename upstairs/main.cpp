// Upstairs - Assignment 3 for course Programming Language
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

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "big_integer.h"
#include "fibonacci.h"
#include "io_util.hpp"

// The I/O mode.
enum IoMode {
  SCREEN_IO = 0,
  FILE_IO,
};

// The computation mode, indicates what kind of method we will use.
enum ComputationMode {
  NONE = 0,
  RECURSIVE,
  ITERATIVE,
};

// The maximal stair value we support.
constexpr int kMaxStair = 10000;

// Lets the user input the I/O mode and the corresponding settings.
IoMode SelectIoMode();

// Right trims the white space of a string.
inline std::string Trim(const std::string &s);

// Prints the answer of the given input number and computation mode (iterative or recursive).
void PrintAnswer(const int &input,
                 const ComputationMode &mode,
                 luolc::upstairs::Fibonacci &fib);

// The executable entrance.
int main() {
  auto fib = luolc::upstairs::Fibonacci(kMaxStair);
  auto io_mode = SelectIoMode();

  std::string input_line; // to store raw string of each line
  auto mode = ComputationMode::NONE; // will be whether RECURSIVE or ITERATIVE
  std::vector<int> inputs; // to cache the user input numbers

  if (io_mode == SCREEN_IO) {
    Println("--- 爬楼梯计算演示程序，支持楼梯数 1 ~", kMaxStair, "范围 ---");
    Println("请选择计算模式：A 递归方法；B 非递归方法");
    Print("Computation mode (A/B): ");
  }

  // Keeps reading lines until reach the EOF
  // It is useful when the user choose the file input/output mode
  while (std::getline(std::cin, input_line)) {
    input_line = Trim(input_line);

    // mode is NONE means: it is the beginning of the current experiment,
    // and we should input the mode first.
    if (mode == NONE) {
      if (input_line == "A") {
        mode = RECURSIVE;
        Println("采用递归方法");
      } else if (input_line == "B") {
        mode = ITERATIVE;
        Println("采用非递归方法");
      } else if (input_line == "0") {
        Println("Bye!");
        break;
      } else {
        Println(R"(输入不合法，请重新输入"A"或"B"，不要包含多余字符)");
        continue;
      }
    } else { // the user should input a number here
      std::istringstream iss(input_line);
      int input; // to store the integer value when the user inputs a number
      iss >> input;
      if (!iss.eof()) {
        Println("输入不合法，请重新输入一个（且仅一个）整数，不要包含多余字符");
        continue;
      }

      if (input == 0) { // the user input zero
        if (io_mode == FILE_IO) {
          // exit
          // file mode does not support interactive input
          Println("Bye!");
          break;
        }

        Println("如需使用另一计算模式重新计算答案，请输入任意字符；若需退出，请直接按下 Enter 键");
        Print("The other mode (<any key>)/ Exit (<nothing>): ");
        std::getline(std::cin, input_line);
        if (!input_line.empty()) {
          auto other_mode = mode == RECURSIVE ? ITERATIVE : RECURSIVE;
          for (const auto &i : inputs) {
            PrintAnswer(i, other_mode, fib);
          }
        }
        Println("Bye!");
        break;
      } else { // the user input a non-zero number
        inputs.push_back(input);
        PrintAnswer(input, mode, fib);
      }
    }
  }
  return 0;
}

IoMode SelectIoMode() {
  std::string input_line;

  Println("请选择输入输出模式：screen 屏幕输入输出 或 file 文件输入输出");
  Print("I/O mode (screen/file): ");

  IoMode result;
  while (true) {
    getline(std::cin, input_line);

    if (input_line == "file") {
      Println("请输入文件输入路径，默认为 input.txt");
      while (true) {
        Print("The path to input file (input.txt): ");
        getline(std::cin, input_line);
        if (input_line.empty()) input_line = "input.txt";
        if (IsFileExists(input_line.c_str())) break;
        Println("路径", input_line, "下文件不存在，请重新输入");
      }
      auto input_file = std::string(input_line).c_str();

      Println("请输入文件输出路径，默认为 output.txt");
      Print("The path to output file (output.txt): ");
      getline(std::cin, input_line);
      auto output_file = input_line.empty() ? "output.txt" : input_line.c_str();

      freopen(input_file, "r", stdin);
      freopen(output_file, "w", stdout);

      result = FILE_IO;
      break;
    } else if (input_line == "screen") {
      result = SCREEN_IO;
      break;
    } else {
      Println("输入不合法，请重新输入 screen 或 file");
    }
  }

  return result;
}

std::string Trim(const std::string &s) {
  auto s_copy = s;
  s_copy.erase(s.find_last_not_of(" \n\r\t") + 1);
  return s_copy;
}

void PrintAnswer(const int &input,
                 const ComputationMode &mode,
                 luolc::upstairs::Fibonacci &fib) {
  if (input < 0 || input > kMaxStair) Println("无法计算，输入超出计算范围 1 ~", kMaxStair);
  else if (mode == RECURSIVE) Println(fib.RecursiveFibonacci(input));
  else Println(fib.IterativeFibonacci(input));
}
