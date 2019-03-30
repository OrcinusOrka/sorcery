#ifndef _SPELL_H_
#define _SPELL_H_
#include "card.h"

class Spell: public Card {
 public:
   Spell(std::string name, std::string type,
         int cost, std::vector<Effect> effects);
   ~Spell();
};

#endif
