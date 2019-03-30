#include "ritual.h"
int Ritual::getCharge() const {
  return charge;
}

void Ritual::setCharge(const int& new_charge) {
  charge = new_charge;
}

Ritual::Ritual(std::string name, std::string type,
             int cost, std::vector<Effect> effects, int charge):
  Card{name, type, cost, effects}, charge{charge} {}

Ritual::~Ritual() {}
