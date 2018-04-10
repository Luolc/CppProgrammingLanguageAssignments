// Pie - Assignment 1 for course Programming Language
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
#include <iostream>

#include "monte_carlo_tester.h"
#include "random_generator.h"
#include "time_limit_runner.h"

// Real pi.
const double pi = std::atan(1) * 4;

// Running time limit.
// Specifically, 10 seconds in this assignment.
const luolc::pie::Millis kTimeLimit = 10000;

// We shall check the running time in each kTimeStep times.
const int kTimeStep = (int) 1e5;

// Calculates the square of the given number.
inline const double Square(const double &x) {
  return x * x;
}

// Calculates the significant figures of the estimation of pie.
inline const int SignificantFiguresOfPie(double estimation) {
  int result = 0;

  double real_pi = pi;
  while (int(real_pi) == int(estimation)) {
    ++result;
    real_pi = 10.0 * (real_pi - int(real_pi));
    estimation = 10.0 * (estimation - int(estimation));
  }

  return result;
}

// The executable entrance.
int main() {
  auto generator = luolc::pie::UniformRandomGenerator(0, 1.0);
  auto tester =
      luolc::pie::MonteCarloTester([&generator] {
        return Square(generator.Generate()) + Square(generator.Generate()) < 1;
      });

  auto runner = luolc::pie::TimeLimitRunner(kTimeLimit, kTimeStep);
  auto running_time = runner.Run([&tester] { tester.Test(); });

  auto estimated_pi = 4.0 * tester.Probability();

  // Outputs
  std::cout << "作者: 骆梁宸 (1400012616)" << std::endl;
  std::cout << "提交时间: 2018-03-28" << std::endl;
  std::cout << "程序的目标和主要方法: 使用蒙特卡罗算法估算圆周率数值" << std::endl;
  std::cout << "程序亮点: 根据要求的运行时间限制进行卡时，以尽可能输出精度更高的结果" << std::endl;
  std::cout << "本次计算的 PI 值为: " << estimated_pi << std::endl;
  std::cout << "运行耗时: " << running_time / 1000 << "." << running_time % 1000 << "s" << std::endl;
  std::cout << "有效数字位数: " << SignificantFiguresOfPie(estimated_pi) << std::endl;

  return 0;
}
