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
// The general battle map in World of Warcraft.

#ifndef WARCRAFT_AZEROTH_H
#define WARCRAFT_AZEROTH_H

#include <functional>
#include <unordered_map>

#include "castle.h"
#include "warrior.h"

namespace luolc {
namespace warcraft {

// Defined in this file.
class Azeroth;

// The general battle map in World of Warcraft.
class Azeroth {
 public:
  // Constructs the land of Azeroth.
  Azeroth(int initial_elements, int n_cities, int n_minutes, const WarriorConfig *warrior_config);
  ~Azeroth();

  // The battle begins!
  void BattleBegin();

 private:
  Castle *alliance_castle_; // blue
  Castle *orcs_castle_; // red

  int time_limit_; // time limit, use 10-seconds as unit

  // actions at each time point, returns whether the war is end
  std::unordered_map<int, std::function<bool()>> action_fn_;

  // Initializes fields.
  void InitCities(int n_cities);
  void InitActionFnMap();
};

} // namespace warcraft
} // namespace luolc

#endif //WARCRAFT_AZEROTH_H
