#ifndef _ENCHANTMENT_H_
#define _ENCHANTMENT_H_

#include "card.h"

class Enchantment: public Card {
 public:
  Enchantment(std::string name, std::string type,
              int cost, std::vector<Effect> effects);
  ~Enchantment();
};
#endif
