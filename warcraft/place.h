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

#ifndef WARCRAFT_PLACE_H
#define WARCRAFT_PLACE_H

#include "warrior.h"

namespace luolc {
namespace warcraft {

// Defined in this file.
class Place;

// The abstract class of Castle and City.
class Place {
 public:
  Place *NextAtWest = nullptr; // the next place at west
  Place *NextAtEast = nullptr; // the next place at east

  // Constructs a place.
  Place();
  explicit Place(int n_elements);
  virtual ~Place();

  // Moves warriors to next place.
  void MoveOrcsWarriorToEast();
  void MoveAllianceWarriorToWest();

  // Sends the message that warriors have arrived this place (city or castle).
  virtual void SendWarriorsArrivedMessage() const = 0;

 protected:
  int n_elements_;

  Warrior *orcs_warrior_ = nullptr;
  Warrior *alliance_warrior_ = nullptr;
};

} // namespace warcraft
} // namespace luolc

#endif //WARCRAFT_PLACE_H
