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
// Defines the abstract Warrior class and the corresponding factory and config class.

#ifndef WARCRAFT_WARRIOR_H
#define WARCRAFT_WARRIOR_H

#include <functional>
#include <string>
#include <unordered_map>

#include "affiliation.h"

namespace luolc {
namespace warcraft {

// Defined in this file.
class WarriorConfig;
class WarriorFactory;
class Warrior;

constexpr const int N_WARRIOR_TYPES = 5;

enum WarriorType {
  DRAGON,
  NINJA,
  ICEMAN,
  LION,
  WOLF,
};

// The config of warriors.
class WarriorConfig {
 public:
  // Gets the initial attack of a type of warrior.
  const int AttackOf(WarriorType type) const;

  // Gets the initial elements of a type of warrior.
  const int InitialElementsOf(WarriorType type) const;

  // Sets the attack and initial elements of warriors.
  void SetAttack(int attack, int index);
  void SetInitialElements(int initial_elements, int index);

 private:
  int attacks_[N_WARRIOR_TYPES];
  int initial_elements_[N_WARRIOR_TYPES];
};

// The factory which produces warriors.
class WarriorFactory {
 public:
  // Constructs a factory with the given WarriorConfig.
  explicit WarriorFactory(const WarriorConfig *config);

  // Produces a new warrior.
  Warrior *Produce(WarriorType type, Affiliation affiliation, int index) const;

 private:
  const WarriorConfig *const config_;

  template<typename T>
  Warrior *RealProduce(WarriorType type, Affiliation affiliation, int index) const;
};

// The abstract class of warrior.
class Warrior {
 public:
  // Constructs a warrior.
  Warrior();
  Warrior(Affiliation affiliation, int index, int attack, int initial_elements);
  virtual ~Warrior();

  // Sends the message that the warrior is born.
  void SendBornMessage() const;

  // Creates a new instance of a specific warrior.
  template<typename T>
  static T *NewInstance(Affiliation affiliation,
                        int index,
                        int attack,
                        int initial_elements);

  // The full name of a warrior, like "red lion 1".
  const std::string FullName() const;

  // The postfix, like "with 100 elements and force 50".
  const std::string ElementsAndForcePostfix() const;

  // Attacks an enemy.
  void Attack(Warrior *enemy);

  // The blood was sucked by the enemy.
  // Note that this method is only useful when a lion was killed.
  void SuckedBloodBy(Warrior *enemy);

  // Returns whether this warrior is dead.
  const bool IsDead() const;

  // Counterattacks an enemy.
  virtual void Counterattack(Warrior *enemy) const;

  // Gets/Sets the winning status.
  void SetIsWinnerInPreviousCity(bool is_winner);
  const bool IsWinnerInPreviousCity() const;

  // Gets reward from the base.
  void GetReward(int n_elements);

  // Whether the warrior should yell if he is alive after an attack.
  virtual bool ShouldYell() const;

  // Actions on move finished.
  virtual void OnMoveFinished();

  // Actions on killed an enemy by attack.
  virtual void OnKilledEnemyByAttack();

 protected:
  int attack_;
  int n_elements_;
  int n_elements_before_fighting_ = 0;

  virtual const char *Name() const = 0;

  virtual void OnAttackStart();
  virtual void OnDefendStart();

 private:
  Affiliation affiliation_;
  int index_;

  bool is_winner_in_previous_city_ = false;
};

} // namespace warcraft
} // namespace luolc

#endif //WARCRAFT_WARRIOR_H
