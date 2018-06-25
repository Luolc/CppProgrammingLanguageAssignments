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
// The base of the alliance and Orcs.

#ifndef WARCRAFT_CASTLE_H
#define WARCRAFT_CASTLE_H

#include "affiliation.h"
#include "place.h"
#include "warrior.h"

namespace luolc {
namespace warcraft {

// Defined in this file.
class Castle;

// The base of the alliance and Orcs.
class Castle : public Place {
 public:
  // Constructs a castle, the base of alliance or Orcs.
  Castle(Affiliation affiliation,
         int initial_elements,
         const WarriorConfig *warrior_config,
         const WarriorType *orders);
  ~Castle() override;

  // Produces a new warrior if there are enough elements in the castle.
  Warrior *ProduceWarrior();

  // Receives elements collected by the warriors.
  void ReceiveElements(int n_elements);

  // Checks whether the castle has been taken by the enemy.
  // Returns true if lost.
  bool CheckIsLostOrNot();

  // Reports the number of current elements in the castle.
  void ReportElements();

  // Rewards the winner in a city.
  void RewardWinner(Warrior *warrior);

  // Sends the message that an enemy has arrived the castle.
  void SendWarriorsArrivedMessage() const override;

 private:
  Affiliation affiliation_;

  // The order of warriors to produce
  // Orcs: iceman、lion、wolf、ninja、dragon
  // Alliance: lion、dragon、ninja、iceman、wolf
  const WarriorType *const orders_;

  const WarriorConfig *const warrior_config_;
  const WarriorFactory *const warrior_factory_;

  // The index of next warrior in orders array. From 0 to 4.
  int next_warrior_position_;

  // The count of enemys in the castle.
  int n_enemys;

  // The count of warriors have been produced in this base.
  int n_warriors_produced_;

  // Sends the message that the base has been taken by the enemy.
  void SendLostMessage() const;
};

} // namespace warcraft
} // namespace luolc

#endif //WARCRAFT_CASTLE_H
