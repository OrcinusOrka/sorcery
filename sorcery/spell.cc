#include "spell.h"

Spell::Spell(std::string name, std::string type,
             int cost, std::vector<Effect> effects):
  Card{name, type, cost, effects} {}

Spell::~Spell() {}
