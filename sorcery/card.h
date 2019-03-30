#ifndef _CARD_H_
#define _CARD_H_

#include <vector>
#include <string>
#include "effect.h"

class Card {
  std::string name;
  std::string type;
  //int owner;
  //int ori_cost;
  int cost;
  std::vector<Effect> effects;
  std::vector<Effect> ori_effects;
 public:
  Card(std::string name, std::string type,
       int cost, std::vector<Effect> effects);
  std::string getName() const;
  std::string getType() const;
  //int getOwner() const;
  int getCost() const; //for spell and enchantment that num is zero
  std::vector<Effect> getEffects() const;
  std::vector<Effect> getOriEffects() const;
  void setEffect(const std::vector<Effect> &);
  virtual ~Card() = 0;
};
#endif
