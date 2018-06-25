// Warcraft - Assignment 7 for course Programming Language
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
// The main executor of the project.

#include <iostream>

#include "azeroth.h"
#include "warrior.h"

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int n_cases;
  std::cin >> n_cases;
  for (int i = 0; i < n_cases; ++i) {
    if (i != 0) std::cout << std::endl;
    std::cout << "Case:" << i + 1 << std::endl;

    int base_initial_elements;
    int n_cities;
    int n_minutes;
    std::cin >> base_initial_elements;
    std::cin >> n_cities;
    std::cin >> n_minutes;

    auto config = new luolc::warcraft::WarriorConfig();
    for (int j = 0; j < 5; ++j) {
      int warrior_initial_elements;
      std::cin >> warrior_initial_elements;
      config->SetInitialElements(warrior_initial_elements, j);
    }
    for (int j = 0; j < 5; ++j) {
      int attack;
      std::cin >> attack;
      config->SetAttack(attack, j);
    }

    auto azeroth = new luolc::warcraft::Azeroth(base_initial_elements, n_cities, n_minutes, config);
    azeroth->BattleBegin();
  }
  return 0;
}