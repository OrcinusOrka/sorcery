#ifndef _MINION_H_
#define _MINION_H_

#include <vector>
#include "minion.h"
#include "player.h"
#include "effect.h"
#include "enchantment.h"
#include "card.h"

class Minion: public Card {
  int ori_atk;
  int atk;
  int ori_def;
  int def;
  int action;
  std::vector<Enchantment> enchantments;
  void validDef();
  void validAtk();
  void update();
 public:
  int getDef() const;
  void setDef(const int &);
  int getAtk() const;
  void setAtk(const int &);
  int getAction() const;
  void setAction(const int&);
  void addEnchantment(Enchantment);
  void popEnchantment();
  const std::vector<Enchantment>& getEnchantments();
  void attack(Minion &);
  void attack(Player &);
  Minion(std::string name, std::string type,
         int cost, std::vector<Effect> effects,
         int atk, int def);
  ~Minion();
};

#endif
