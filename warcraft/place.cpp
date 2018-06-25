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
// The abstract class of Castle and City.

#include "place.h"

#include <stdexcept>

namespace luolc {
namespace warcraft {

Place::Place() : n_elements_(0) {
};

Place::Place(int n_elements)
    : n_elements_(n_elements) {
}

Place::~Place() {
  delete orcs_warrior_;
  delete alliance_warrior_;
}

void Place::MoveOrcsWarriorToEast() {
  if (orcs_warrior_ && NextAtEast) {
    if (NextAtEast->orcs_warrior_) {
      throw std::runtime_error("there is already an orcs warrior in next place");
    }
    orcs_warrior_->OnMoveFinished();
    NextAtEast->orcs_warrior_ = orcs_warrior_;
    orcs_warrior_ = nullptr;
  }
}

void Place::MoveAllianceWarriorToWest() {
  if (alliance_warrior_ && NextAtWest) {
    if (NextAtWest->alliance_warrior_) {
      throw std::runtime_error("there is already an alliance warrior in next place");
    }
    alliance_warrior_->OnMoveFinished();
    NextAtWest->alliance_warrior_ = alliance_warrior_;
    alliance_warrior_ = nullptr;

  }
}

} // namespace warcraft
} // namespace luolc
