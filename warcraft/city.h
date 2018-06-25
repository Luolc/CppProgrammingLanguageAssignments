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
// The place where the battle takes place.

#ifndef WARCRAFT_CITY_H
#define WARCRAFT_CITY_H

#include "castle.h"
#include "place.h"

namespace luolc {
namespace warcraft {

// Defined in this file.
class City;

// The place where the battle takes place.
class City : public Place {
 public:
  // Constructs a city with its index.
  City(int index, Castle *alliance_castle, Castle *orcs_castle);
  ~City() override;

  // Produces ten elements in the city.
  void ProduceElements();

  // The warrior collect the elements in the city if he is alone.
  void WarriorsCollectElements();

  // Sends the message that warriors have arrived the city.
  void SendWarriorsArrivedMessage() const override;

  // Fight if there are two warriors in the city,
  // including attack, counterattack, yelling and raising flags.
  void Fight();

  // Winners get reward elements from their base.
  void AllianceWinnerGetReward();
  void OrcsWinnerGetReward();

 private:
  int index_; // the index of the city
  Affiliation flag_; // the affiliation of current flag
  Affiliation previous_winner_; // the previous winner in the last fight

  Castle *alliance_castle_;
  Castle *orcs_castle_;
};

} // namespace warcraft
} // namespace luolc

#endif //WARCRAFT_CITY_H
