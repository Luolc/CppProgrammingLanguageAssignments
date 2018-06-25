//
// Created by 骆梁宸 on 2018/6/22.
//

#include "warrior.h"

#include <sstream>

#include "dragon.h"
#include "event.h"
#include "iceman.h"
#include "lion.h"
#include "ninja.h"
#include "wolf.h"

namespace luolc {
namespace warcraft {

const int WarriorConfig::AttackOf(WarriorType type) const {
  return attacks_[type];
}

const int WarriorConfig::InitialElementsOf(WarriorType type) const {
  return initial_elements_[type];
}

void WarriorConfig::SetAttack(int attack, int index) {
  attacks_[index] = attack;
}

void WarriorConfig::SetInitialElements(int initial_elements, int index) {
  initial_elements_[index] = initial_elements;
}

WarriorFactory::WarriorFactory(const WarriorConfig *config) : config_(config) {
}

Warrior *WarriorFactory::Produce(WarriorType type,
                                 Affiliation affiliation,
                                 int index) const {
  switch (type) {
    case DRAGON:return RealProduce<Dragon>(DRAGON, affiliation, index);
    case NINJA:return RealProduce<Ninja>(NINJA, affiliation, index);
    case ICEMAN:return RealProduce<Iceman>(ICEMAN, affiliation, index);
    case LION:return RealProduce<Lion>(LION, affiliation, index);
    case WOLF:return RealProduce<Wolf>(WOLF, affiliation, index);
    default:throw std::invalid_argument("No matching WarriorType");
  }
}

template<typename T>
Warrior *WarriorFactory::RealProduce(WarriorType type,
                                     Affiliation affiliation,
                                     int index) const {
  return Warrior::NewInstance<T>(
      affiliation, index, config_->AttackOf(type), config_->InitialElementsOf(type));
}

Warrior::Warrior() = default;

Warrior::Warrior(Affiliation affiliation, int index, int attack, int initial_elements)
    : affiliation_(affiliation),
      index_(index),
      attack_(attack),
      n_elements_(initial_elements) {
  event::SendMessage(FullName() + " born");
}

Warrior::~Warrior() = default;

void Warrior::SendBornMessage() const {
  event::SendMessage(FullName() + " born");
}

template<typename T>
T *Warrior::NewInstance(Affiliation affiliation,
                        int index,
                        int attack,
                        int initial_elements) {
  auto instance = new T();
  auto base_instance = (Warrior *) instance;

  base_instance->affiliation_ = affiliation;
  base_instance->index_ = index;
  base_instance->attack_ = attack;
  base_instance->n_elements_ = initial_elements;

  base_instance->SendBornMessage();

  return (T *) base_instance;
}

const std::string Warrior::FullName() const {
  std::ostringstream oss;
  if (affiliation_ == ALLIANCE) oss << "blue";
  else oss << "red";
  oss << " " << Name() << " " << index_;
  return oss.str();
}

const std::string Warrior::ElementsAndForcePostfix() const {
  return "with " + std::to_string(n_elements_) + " elements and force " + std::to_string(attack_);
}

void Warrior::Attack(Warrior *enemy) {
  OnAttackStart();
  enemy->OnDefendStart();
  enemy->n_elements_ -= attack_;
}

void Warrior::SuckedBloodBy(Warrior *enemy) {
  enemy->n_elements_ += n_elements_before_fighting_;
}

const bool Warrior::IsDead() const {
  return n_elements_ <= 0;
}

void Warrior::Counterattack(Warrior *enemy) const {
  enemy->n_elements_ -= attack_ / 2;
}

void Warrior::SetIsWinnerInPreviousCity(bool is_winner) {
  is_winner_in_previous_city_ = is_winner;
}

const bool Warrior::IsWinnerInPreviousCity() const {
  return is_winner_in_previous_city_;
}

void Warrior::GetReward(int n_elements) {
  n_elements_ += n_elements;
}

bool Warrior::ShouldYell() const {
  return false;
}

void Warrior::OnMoveFinished() {
}

void Warrior::OnKilledEnemyByAttack() {
}

void Warrior::OnAttackStart() {
}

void Warrior::OnDefendStart() {
}

} // namespace warcraft
} // namespace luolc
