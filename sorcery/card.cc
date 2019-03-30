#include "card.h"

std::string Card::getName() const {
  return name;
}

std::string Card::getType() const {
  return type;
}

int Card::getCost() const {
  return cost;
}

std::vector<Effect> Card::getEffects() const {
  return effects;
}

std::vector<Effect> Card::getOriEffects() const {
  return ori_effects;
}

void Card::setEffect(const std::vector<Effect> &new_effects) {
  effects = new_effects;
}

Card::~Card() {}

Card::Card(std::string name, std::string type,
           int cost, std::vector<Effect> effects):
           name{name}, type{type}, cost{cost},
           effects{effects}, ori_effects{effects} {}
