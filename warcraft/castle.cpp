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

#include "castle.h"

#include <string>

#include "event.h"

namespace luolc {
namespace warcraft {

Castle::Castle(Affiliation affiliation,
               int initial_elements,
               const WarriorConfig *warrior_config,
               const WarriorType *orders)
    : Place(initial_elements),
      affiliation_(affiliation),
      warrior_config_(warrior_config),
      warrior_factory_(new WarriorFactory(warrior_config)),
      orders_(orders),
      next_warrior_position_(0),
      n_enemys(0),
      n_warriors_produced_(0) {
}

Castle::~Castle() {
  delete warrior_factory_;
  delete[] orders_;

  Place::~Place();
}

Warrior *Castle::ProduceWarrior() {
  auto warrior_type = orders_[next_warrior_position_];
  auto elements_required = warrior_config_->InitialElementsOf(warrior_type);

  if (n_elements_ >= elements_required) {
    n_elements_ -= elements_required;
    next_warrior_position_ = (next_warrior_position_ + 1) % N_WARRIOR_TYPES;
    auto warrior = warrior_factory_->Produce(warrior_type, affiliation_, ++n_warriors_produced_);

    if (affiliation_ == ALLIANCE) alliance_warrior_ = warrior;
    else orcs_warrior_ = warrior;

    return warrior;
  } else {
    return nullptr;
  }
}

void Castle::ReceiveElements(int n_elements) {
  n_elements_ += n_elements;
}

bool Castle::CheckIsLostOrNot() {
  if (affiliation_ == ALLIANCE) {
    if (orcs_warrior_) {
      if (n_enemys > 0) {
        SendLostMessage();
        return true;
      } else {
        n_enemys += 1;
        delete orcs_warrior_;
        orcs_warrior_ = nullptr; // mission finished; do nothing in the future.
      }
    }
  } else {
    if (alliance_warrior_) {
      if (n_enemys > 0) {
        SendLostMessage();
        return true;
      } else {
        n_enemys += 1;
        delete alliance_warrior_;
        alliance_warrior_ = nullptr; // mission finished; do nothing in the future.
      }
    }
  }

  return false;
}

void Castle::ReportElements() {
  auto msg = std::to_string(n_elements_) + " elements in ";
  if (affiliation_ == ALLIANCE) msg += "blue";
  else msg += "red";
  msg += " headquarter";

  event::SendMessage(msg);
}

void Castle::RewardWinner(Warrior *warrior) {
  if (n_elements_ >= 8) {
    n_elements_ -= 8;
    warrior->GetReward(8);
  }
}

void Castle::SendWarriorsArrivedMessage() const {
  if (affiliation_ == ALLIANCE && orcs_warrior_) {
    auto msg = orcs_warrior_->FullName() + " reached blue headquarter "
        + orcs_warrior_->ElementsAndForcePostfix();
    event::SendMessage(msg);
  } else if (affiliation_ == ORCS && alliance_warrior_) {
    auto msg = alliance_warrior_->FullName() + " reached red headquarter "
        + alliance_warrior_->ElementsAndForcePostfix();
    event::SendMessage(msg);
  }
}

void Castle::SendLostMessage() const {
  std::string msg = " headquarter was taken";
  if (affiliation_ == ALLIANCE) msg = "blue" + msg;
  else msg = "red" + msg;

  event::SendMessage(msg);
}

} // namespace warcraft
} // namespace luolc
