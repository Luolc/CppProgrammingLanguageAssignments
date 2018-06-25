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

#include "city.h"

#include "event.h"

namespace luolc {
namespace warcraft {

City::City(int index, Castle *alliance_castle, Castle *orcs_castle) :
    Place(),
    index_(index),
    flag_(NONE),
    previous_winner_(NONE),
    alliance_castle_(alliance_castle),
    orcs_castle_(orcs_castle) {
}

City::~City() {
  Place::~Place();
}

void City::ProduceElements() {
  n_elements_ += 10;
}

void City::WarriorsCollectElements() {
  if (n_elements_ == 0) return;

  if (orcs_warrior_ != nullptr && alliance_warrior_ == nullptr) {
    auto msg = orcs_warrior_->FullName() + " earned " + std::to_string(n_elements_)
        + " elements for his headquarter";
    event::SendMessage(msg, index_, 7);

    orcs_castle_->ReceiveElements(n_elements_);
    n_elements_ = 0;
  } else if (alliance_warrior_ != nullptr && orcs_warrior_ == nullptr) {
    auto msg = alliance_warrior_->FullName() + " earned " + std::to_string(n_elements_)
        + " elements for his headquarter";
    event::SendMessage(msg, index_, 7);

    alliance_castle_->ReceiveElements(n_elements_);
    n_elements_ = 0;
  }
}

void City::SendWarriorsArrivedMessage() const {
  if (orcs_warrior_) {
    auto msg = orcs_warrior_->FullName() + " marched to city " + std::to_string(index_) + " "
        + orcs_warrior_->ElementsAndForcePostfix();
    event::SendMessage(msg);
  }

  if (alliance_warrior_) {
    auto msg = alliance_warrior_->FullName() + " marched to city " + std::to_string(index_) + " "
        + alliance_warrior_->ElementsAndForcePostfix();
    event::SendMessage(msg);
  }
}

void City::Fight() {
  if (orcs_warrior_ == nullptr || alliance_warrior_ == nullptr) return;

  // defines the attacker and defender.
  Warrior *attacker;
  Warrior *defender;
  if (flag_ == ORCS || (flag_ == NONE && index_ % 2 == 1)) {
    attacker = orcs_warrior_;
    defender = alliance_warrior_;
  } else {
    attacker = alliance_warrior_;
    defender = orcs_warrior_;
  }
  attacker->SetIsWinnerInPreviousCity(false);
  defender->SetIsWinnerInPreviousCity(false);

  // attack
  auto msg = attacker->FullName() + " attacked " + defender->FullName() + " in city "
      + std::to_string(index_) + " " + attacker->ElementsAndForcePostfix();
  event::SendMessage(msg, index_, 3);
  attacker->Attack(defender);

  if (defender->IsDead()) { // the defender is dead in the attack
    attacker->OnKilledEnemyByAttack();
    defender->SuckedBloodBy(attacker);

    attacker->SetIsWinnerInPreviousCity(true);
    msg = defender->FullName() + " was killed in city " + std::to_string(index_);
    event::SendMessage(msg, index_, 5);

    // raise flags
    if (previous_winner_ == ALLIANCE && attacker == alliance_warrior_ && flag_ != ALLIANCE) {
      msg = std::string("blue flag raised in city ") + std::to_string(index_);
      event::SendMessage(msg, index_, 8);

      flag_ = ALLIANCE;
    } else if (previous_winner_ == ORCS && attacker == orcs_warrior_ && flag_ != ORCS) {
      msg = std::string("red flag raised in city ") + std::to_string(index_);
      event::SendMessage(msg, index_, 8);

      flag_ = ORCS;
    }

    delete defender;

    if (attacker == alliance_warrior_) {
      previous_winner_ = ALLIANCE;
      orcs_warrior_ = nullptr;
    } else {
      previous_winner_ = ORCS;
      alliance_warrior_ = nullptr;
    }
  } else {
    // counterattack begin if the defender is not dead
    msg = defender->FullName() + " fought back against " + attacker->FullName() + " in city "
        + std::to_string(index_);
    event::SendMessage(msg, index_, 4);
    defender->Counterattack(attacker);

    if (attacker->IsDead()) { // the attacker is dead in the counterattack
      attacker->SuckedBloodBy(defender);

      defender->SetIsWinnerInPreviousCity(true);
      msg = attacker->FullName() + " was killed in city " + std::to_string(index_);
      event::SendMessage(msg, index_, 5);

      // raise flags
      if (previous_winner_ == ALLIANCE && defender == alliance_warrior_ && flag_ != ALLIANCE) {
        msg = std::string("blue flag raised in city ") + std::to_string(index_);
        event::SendMessage(msg, index_, 8);

        flag_ = ALLIANCE;
      } else if (previous_winner_ == ORCS && defender == orcs_warrior_ && flag_ != ORCS) {
        msg = std::string("red flag raised in city ") + std::to_string(index_);
        event::SendMessage(msg, index_, 8);

        flag_ = ORCS;
      }

      delete attacker;
      attacker = nullptr;

      if (defender == alliance_warrior_) {
        previous_winner_ = ALLIANCE;
        orcs_warrior_ = nullptr;
      } else {
        previous_winner_ = ORCS;
        alliance_warrior_ = nullptr;
      }
    } else { // on one is dead
      previous_winner_ = NONE;
    }
  }

  if (attacker && attacker->ShouldYell()) {
    msg = attacker->FullName() + " yelled in city " + std::to_string(index_);
    event::SendMessage(msg, index_, 6);
  }
}

void City::AllianceWinnerGetReward() {
  if (alliance_warrior_ && alliance_warrior_->IsWinnerInPreviousCity()) {
    alliance_castle_->RewardWinner(alliance_warrior_);
  }
}

void City::OrcsWinnerGetReward() {
  if (orcs_warrior_ && orcs_warrior_->IsWinnerInPreviousCity()) {
    orcs_castle_->RewardWinner(orcs_warrior_);
  }
}

} // namespace warcraft
} // namespace luolc
