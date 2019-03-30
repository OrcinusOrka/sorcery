#include "minion.h"
#include "effect.h"
#include "enchantment.h"
#include <iostream>

int Minion::getDef() const {
  return def;
}

void Minion::setDef(const int &new_def) {
  def = new_def; // if def == 0, move to graveyard. impl it in board.h
                 // dont forget it.
  validDef();
}

int Minion::getAtk() const{
  return atk;
}

void Minion::setAtk(const int &new_atk) {
  atk = new_atk;
  validAtk();
}

int Minion::getAction() const {
  return action;
}

void Minion::setAction(const int & new_action) {
  action = new_action;
  if(action > 1) {
    action = 1;
  }
}

void Minion::addEnchantment(Enchantment new_enchantment) {
  enchantments.emplace_back(new_enchantment);
  update();
  std::cout << "added enchantment and updated the minion" << std::endl; //for_test
}

void Minion::popEnchantment() {
  if(enchantments.size() > 0) {
    enchantments.pop_back();
    update();
  }
}

void Minion::update() {  //AtkDef Scilence Cost can be used as enChantments
  int new_atk = ori_atk;
  int new_def = ori_def;
  std::vector<Effect> new_ability = getOriEffects();
  for(int i = 0; i < enchantments.size(); i++) {
    std::vector<Effect> tmp = enchantments[i].getEffects();
    for(int j = 0; j < tmp.size(); j++) {
      if(tmp[j].ability == Ability::AtkDef) { //AtkDef Scilence
        //std::cout << "change the AtkDef" << std::endl; //for_test
        new_atk += tmp[j].num1;
        new_def += tmp[j].num2;
      } else if(tmp[j].ability == Ability::Silence) {
        for(int k = 0; k < new_ability.size(); k++) {
          new_ability[k].is_scilence = true;
        }
      } else if(tmp[j].ability == Ability::MoreCost) {
        for(int k = 0; k < new_ability.size(); k++) {
          new_ability[k].cost += tmp[j].num1;
          if(new_ability[k].cost < 0) {
            new_ability[k].cost = 0;
          }
        }
      }
    }
  }
  atk = new_atk;
  validAtk();
  def = new_def;
  validDef();
  setEffect(new_ability);
}

void Minion::validDef() {
  if(def < 0) {
    def = 0;
  }
}

void Minion::validAtk() {
  if(atk < 0) {
    atk = 0;
  }
}

void Minion::attack(Minion &target) {
  def = def - target.getAtk();
  validDef();
  int tmp_def = target.getDef();
  tmp_def = tmp_def - atk;
  target.setDef(tmp_def);
}

void Minion::attack(Player &target) {
  int tmp_health = target.getHealth();
  tmp_health -= atk;
  target.setHealth(tmp_health);
}

Minion::Minion(std::string name, std::string type,
               int cost, std::vector<Effect> effects,
               int atk, int def):
               Card{name, type, cost, effects}, ori_atk{atk}, atk{atk},
               ori_def{def}, def{def}, action{1} {
   std::vector<Enchantment> tmp;
   enchantments = tmp;
}

const std::vector<Enchantment> &Minion::getEnchantments(){
    return enchantments;
}

Minion::~Minion() {}
