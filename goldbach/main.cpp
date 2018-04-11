// Goldbach - Assignment 2 for course Programming Language
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

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

#include "primes.h"

// The segment size for primes sieving.
constexpr int kSegmentSize = (int) 5e7;

// Prints the argument.
template<typename T>
inline void Print(const T &output) {
  std::cout << output;
}

// Prints the arguments one by one with a space separator.
template<typename First, typename ... Rest>
inline void Print(const First &first, const Rest &...rest) {
  std::cout << first << " ";
  Print(rest...);
}

// Prints a newline.
inline void Println() {
  std::cout << std::endl;
}

// Prints the arguments one by one with a space separator and turn to the newline.
template<typename ... Outputs>
inline void Println(const Outputs &...outputs) {
  Print(outputs...);
  Println();
}

// The executable entrance.
int main() {
  Println("正在初始化种子素数表……");
  auto prime_utils = luolc::goldbach::Primes(kSegmentSize);
  Println("初始化完成");
  Println("说明：");
  Println("  - 对于 1e8 数量级的输入，可以在常数时间内输出；");
  Println("  - 原则上支持任一 max long long int (2^63) 范围内的数字，但大数所需时间将会非常长；");
  Println("  - 参考运行时间：2s per 1e8；");

  std::string inputLine;
  luolc::goldbach::Integer input;
  bool output_all_answers; // whether to print all the answers for an input
  while (true) {
    Println("------");
    Println("请输入任一整数；如需输出全部素数组合，请在整数前添加一个负号，例如 \"-20\"：");

    while (true) {
      std::getline(std::cin, inputLine);
      std::istringstream iss(inputLine);
      iss >> input;
      if (iss.eof()) break;
      Println("输入不合法，请重新输入一个 (且仅一个) 整数，不要包含行末空格：");
    }

    if (input == 0) {
      Println("Bye!");
      break;
    }

    // Keep expanding the bag-of-primes
    prime_utils.ExpandPrimes();

    output_all_answers = input < 0;
    input = std::abs(input);

    if (input % 2 == 1) {
      Println(input, "是奇数，不能验证哥德巴赫猜想");
      continue;
    }

    if (input <= 2) {
      Println(input, "小于等于2，不能验证哥德巴赫猜想");
      continue;
    }

    if (prime_utils.MaxSize() < input) {
      Println("当前输入数字较大，需要扩充素数表，请稍候……");
      while (prime_utils.MaxSize() < input) prime_utils.ExpandPrimes();
    }

    for (const auto &p : prime_utils.GetPrimes()) {
      if (p * 2 > input) break;
      if (prime_utils.IsPrime(input - p)) {
        Println(input, "=", p, "+", input - p);
        if (!output_all_answers) break;
      }
    }
  }

  return 0;
}
