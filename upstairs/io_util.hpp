// Utilities for course Programming Language
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
// IO utilities.

#ifndef IO_UTIL_H
#define IO_UTIL_H

#include <cstdio>
#include <iostream>

// Prints the argument.
template<typename T>
inline void Print(const T &output);

// Prints the arguments one by one with a space separator.
template<typename First, typename ... Rest>
inline void Print(const First &first, const Rest &...rest);

// Prints a newline.
inline void Println();

// Prints the arguments one by one with a space separator and turn to the newline.
template<typename ... Outputs>
inline void Println(const Outputs &...outputs);

// Checks whether a file with the given file path exists.
inline bool IsFileExists(const char *file_path);

// --- Implementations ---
template<typename First, typename... Rest>
void Print(const First &first, const Rest &... rest) {
  std::cout << first << " ";
  Print(rest...);
}

template<typename T>
void Print(const T &output) {
  std::cout << output;
}

void Println() {
  std::cout << std::endl;
}

template<typename... Outputs>
void Println(const Outputs &... outputs) {
  Print(outputs...);
  Println();
}

bool IsFileExists(const char *file_path) {
  if (FILE *file = fopen(file_path, "r")) {
    fclose(file);
    return true;
  } else {
    return false;
  }
}

#endif //IO_UTIL_H
