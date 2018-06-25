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

#include "azeroth.h"

#include "city.h"
#include "event.h"

namespace luolc {
namespace warcraft {

Azeroth::Azeroth(int initial_elements, int n_cities, int n_minutes,
                 const WarriorConfig *warrior_config) {
  event::Clear();
  time_limit_ = n_minutes / 10;

  alliance_castle_ = new Castle(
      ALLIANCE, initial_elements, warrior_config,
      new WarriorType[N_WARRIOR_TYPES]{LION, DRAGON, NINJA, ICEMAN, WOLF});
  orcs_castle_ = new Castle(
      ORCS, initial_elements, warrior_config,
      new WarriorType[N_WARRIOR_TYPES]{ICEMAN, LION, WOLF, NINJA, DRAGON});

  InitCities(n_cities);
  InitActionFnMap();
}

Azeroth::~Azeroth() {
  for (Place *place = orcs_castle_; place; place = place->NextAtEast) {
    delete place;
  }
}

void Azeroth::InitCities(int n_cities) {
  auto city = new City(1, alliance_castle_, orcs_castle_);
  orcs_castle_->NextAtEast = city;
  city->NextAtWest = orcs_castle_;
  for (int i = 2; i <= n_cities; ++i) {
    auto next_city = new City(i, alliance_castle_, orcs_castle_);
    city->NextAtEast = next_city;
    next_city->NextAtWest = city;
    city = next_city;
  }
  city->NextAtEast = alliance_castle_;
  alliance_castle_->NextAtWest = city;
}

void Azeroth::InitActionFnMap() {
  action_fn_[0] = [this]() {
    orcs_castle_->ProduceWarrior();
    alliance_castle_->ProduceWarrior();
    return false;
  };
  action_fn_[1] = [this]() {
    for (auto place = orcs_castle_->NextAtEast; place; place = place->NextAtEast) {
      place->MoveAllianceWarriorToWest();
    }
    for (auto place = alliance_castle_->NextAtWest; place; place = place->NextAtWest) {
      place->MoveOrcsWarriorToEast();
    }

    for (Place *place = orcs_castle_; place; place = place->NextAtEast) {
      place->SendWarriorsArrivedMessage();
    }

    auto is_end = alliance_castle_->CheckIsLostOrNot() || orcs_castle_->CheckIsLostOrNot();

    return is_end;
  };
  action_fn_[2] = [this]() {
    for (auto city = orcs_castle_->NextAtEast; city != alliance_castle_; city = city->NextAtEast) {
      ((City *) city)->ProduceElements();
    }
    return false;
  };
  action_fn_[3] = [this]() {
    for (auto city = orcs_castle_->NextAtEast; city != alliance_castle_; city = city->NextAtEast) {
      ((City *) city)->WarriorsCollectElements();
    }
    return false;
  };
  action_fn_[4] = [this]() {
    for (auto city = orcs_castle_->NextAtEast; city != alliance_castle_; city = city->NextAtEast) {
      ((City *) city)->Fight();
    }

    for (auto city = orcs_castle_->NextAtEast; city != alliance_castle_; city = city->NextAtEast) {
      ((City *) city)->AllianceWinnerGetReward();
    }
    for (auto city = alliance_castle_->NextAtWest; city != orcs_castle_; city = city->NextAtWest) {
      ((City *) city)->OrcsWinnerGetReward();
    }

    for (auto city = orcs_castle_->NextAtEast; city != alliance_castle_; city = city->NextAtEast) {
      ((City *) city)->WarriorsCollectElements();
    }

    return false;
  };
  action_fn_[5] = [this]() {
    orcs_castle_->ReportElements();
    alliance_castle_->ReportElements();
    return false;
  };
}

void Azeroth::BattleBegin() {
  for (int i = 0; i <= time_limit_; ++i) {
    auto is_end = action_fn_[i % 6]();

    event::PrintMessages();
    event::AddTenMinutes();

    if (is_end) break;
  }
}

} // namespace warcraft
} // namespace luolc
