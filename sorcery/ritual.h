#ifndef _RITUAL_H_
#define _RITUAL_H_
#include "card.h"

class Ritual: public Card {
  int charge;
 public:
   Ritual(std::string name, std::string type,
          int cost, std::vector<Effect> effects, int charge);
  ~Ritual();
  int getCharge() const;
  void setCharge(const int&);
};

#endif
