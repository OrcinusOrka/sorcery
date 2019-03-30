#include "board.h"
#include "cardscollection.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

#define use_textdisplay 1 // 0 represents not using textdisplay, otherwise use textdisplay

void Board::textDisplayMassage(const std::string & message) {
  #if use_textdisplay
  std::cout << message << std::endl;
  #endif
}

void Board::summon(std::string summonMonster, const int &num) {
  const int index = turn % 2; //check trigger
  const int oppoent_index = (turn + 1) % 2;
  for(int i = 0; i < num; i++) {
    if(minions[index].size() < 5) {
      Minion new_minion = createMinion(summonMonster);
      minions[index].emplace_back(new_minion);
      #if 1 //for_test
      int new_i = minions[index].size() - 1;
      checkTrigger(Trigger::OwnSummon, index, index, new_i); //checkTrigger
      checkTrigger(Trigger::OppoentSummon, oppoent_index, index, new_i);
      checkTrigger(Trigger::Summon, oppoent_index, index, new_i);
      checkTrigger(Trigger::Summon, index, index, new_i);
      #endif
    } else {
    }
  }
}

bool Board::exist_minions(const int &target, const int& i) {
  if(minions[i].size() > target) {
    return true;
  } else {
    return false;
  }
}

void Board::minionDie(const int &target, const int &i) {
  std::string mon = minions[i][target].getName();
  players[i].toGraveyard(mon);
  minions[i].erase(minions[i].begin() + target);
}

void Board::setDef(const int &target, const int &i, const int &new_def) {
  if(exist_minions(target, i)) {
    minions[i][target].setDef(new_def);
    if(minions[i][target].getDef() <= 0) {
      minionDie(target, i);
    }
  }
}

void Board::destory(const int &target, const int &index) {
  if(!exist_minions(target, index) && target != 5) {
    return;
  }
  if(target >= 0 && target < 5) {
    minions[index].erase(minions[index].begin()+target);
  } else {
    rituals[index] = EmptyRitual;
  }
}


void Board::AtkDef(const int &target, const int &index,
                   const int &atk_num, const int &def_num) {
  if(exist_minions(target, index)) {
    int new_def = minions[index][target].getDef() + def_num;
    int new_atk = minions[index][target].getAtk() + atk_num;
    minions[index][target].setAtk(new_atk);
    setDef(target, index, new_def);
  }
}

void Board::unsummon(const int &target, const int &index) {
  if(exist_minions(target, index)) {
    std::string card = minions[index][target].getName();
    players[index].addHand(card);
    minions[index].erase(minions[index].begin() + target);
  }
}

void Board::recharge(const int &charge_num) {
  const int index = turn % 2;
  int new_charge = rituals[index].getCharge() + charge_num;
  rituals[index].setCharge(new_charge);
}

void Board::disenchant(const int &target) {
  const int index = (turn + 1) % 2;
  minions[index][target].popEnchantment();
}

void Board::resurrect() {
  const int index = turn % 2;
  std::string name = players[index].getGraveyard();
  players[index].rm_graveyard();
  if(name != "") {
    summon(name);
  }
}

void Board::HealthMana(const int &index, const int &health_num, const int &mana_num) {
    players[index].setHealth(players[index].getHealth() + health_num);
    players[index].setMana(players[index].getMana() + mana_num);
}

void Board::init(const std::string &deck1 , const std::string &deck2) {
  srand(time(0));
  Player tmp1;
  Player tmp2;
  tmp1.init(deck1, is_test, rand()%100 );
  players.emplace_back(tmp1);
  tmp2.init(deck2, is_test, rand()%100 );
  players.emplace_back(tmp2);
  rituals.emplace_back(EmptyRitual);
  rituals.emplace_back(EmptyRitual);
  minions.resize(2);
  turn = 0;
}

void Board::testMode() {
  is_test = true;
}

void Board::attack(const int &target) {
  const int index = turn % 2;
  const int oppoent_index = (turn + 1) % 2;
  if(!exist_minions(target, index)) {
    textDisplayMassage("The minion as a attacker doesn't exist");
    return;
  }
  if(minions[index][target].getAction() > 0) {
    int new_action = minions[index][target].getAction() - 1;
    minions[index][target].attack(players[oppoent_index]);
    minions[index][target].setAction(new_action);
  } else {
    textDisplayMassage("No enough action point");
  }
}

void Board::attack(const int &subject_i, const int &object_i) {
  const int index = turn % 2;
  const int oppoent_index = (turn + 1) % 2;
  if(!exist_minions(subject_i, index)) {
    textDisplayMassage("The minion as a attacker doesn't exist.");
    return;
  }
  if(!exist_minions(object_i, oppoent_index)) {
    textDisplayMassage("The target minion doesn't exist.");
    return;
  }
  if(minions[index][subject_i].getAction() > 0) {
    int new_action = minions[index][subject_i].getAction() - 1;
    minions[index][subject_i].setAction(new_action);
    minions[index][subject_i].attack(minions[oppoent_index][object_i]);
    if(minions[index][subject_i].getDef() <= 0) {
      minionDie(subject_i, index);
    }
    if(minions[oppoent_index][object_i].getDef() <= 0) {
      minionDie(object_i, oppoent_index);
    }
  } else {
    textDisplayMassage("No enough action point.");
  }
}

std::string Board::whatType(std::string card) {
  std::string rv = "no this card";
  if(card == "Air Elemental" ||
     card == "Earth Elemental" ||
     card == "Fire Elemental" ||
     card == "Potion Seller" ||
     card == "Novice Pyromancer" ||
     card == "Apprentice Summoner" ||
     card == "Master Summoner") {
    rv = "Minion";
  } else if (card == "Banish" ||
             card == "Unsummon" ||
             card == "Recharge" ||
             card == "Disenchant" ||
             card == "Raise Dead" ||
             card == "Blizzard") {
    rv = "Spell";
  } else if (card == "Giant Strength" ||
             card == "Magic Fatigue" ||
             card == "Silence") {
    rv = "Enchantment";
  } else if (card == "Dark Ritual" ||
             card == "Aura of Power" ||
             card == "Standstill") {
    rv = "Ritual";
  }
  return rv;
}

Minion Board::createMinion(std::string new_card) {
  if(new_card == "Air Elemental") return AirElemental;
  if(new_card == "Earth Elemental") return EarthElemental;
  if(new_card == "Fire Elemental") return FireElemental;
  if(new_card == "Potion Seller") return PotionSeller;
  if(new_card == "Novice Pyromancer") return NovicePyromancer;
  if(new_card == "Apprentice Summoner") return ApprenticeSummoner;
  if(new_card == "Master Summoner") return MasterSummoner;
  return EmptyMinion;
}

Spell Board::createSpell(std::string new_card) {
  if(new_card == "Banish") return Banish;
  if(new_card == "Unsummon") return Unsummon;
  if(new_card == "Recharge") return Recharge;
  if(new_card == "Disenchant") return Disenchant;
  if(new_card == "Raise Dead") return RaiseDead;
  if(new_card == "Blizzard") return Blizzard;
  return  EmptySpell;
}

Enchantment Board::createEchantment(std::string new_card) {
  if(new_card == "Giant Strength") return GiantStrength;
  if(new_card == "Magic Fatigue") return MagicFatigue;
  if(new_card == "Silence") return Silence;
  return  EmptyEnchantment;
}

Ritual Board::createRitual(std::string new_card) {
  if(new_card == "Dark Ritual") return DarkRitual;
  if(new_card == "Aura of Power") return AuraofPower;
  if(new_card == "Standstill") return Standstill;
  return EmptyRitual;
}

void Board::use(const int &target) {
  const int index = turn % 2;
  if(!exist_minions(target, index)) {
    textDisplayMassage("The minions does't exist");
    return;
  }
  Effect ability = minions[index][target].getEffects().back();
  if(ability.is_scilence == true) {
    textDisplayMassage("The minion is silent");
    return;
  }
  if( !exist_minions(target, index) ) {
    textDisplayMassage("The minion doesn't exist");
    return;
  }
  if( minions[index][target].getAction() <= 0 ) {
    textDisplayMassage("No action point");
    return;
  }
  if( players[index].getMana() < ability.cost ) {
    textDisplayMassage("No enough Mana");
    return;
  }
  if( ability.target != Target::No &&
      ability.trigger != Trigger::None ) {
    textDisplayMassage("This ability need a target or activated by trigger.");
    return;
  }
  if ( ability.ability == Ability::Summon ) {
    if(minions[index].size() >= 5) {
      textDisplayMassage("The minions slots are full");
      return;
    }
    minions[index][target].setAction(minions[index][target].getAction() - 1);
    players[index].setMana(players[index].getMana() - ability.cost);
    summon(ability.summonMonster, ability.num1);
  }
}

void Board::use(const int &i, const int &p, const int &t) {
  const int index = turn % 2;
  if(!exist_minions(i, index)) {
    textDisplayMassage("The minion does't exist");
    return;
  }
  Effect ability = minions[index][i].getEffects().back();
  if(ability.is_scilence == true) {
    textDisplayMassage("The minion is silent");
    return;
  }
  if( minions[index][i].getAction() <= 0 ) {
    textDisplayMassage("No enough action point");
    return;
  }
  if( players[index].getMana() < ability.cost ) {
    textDisplayMassage("No enough Mana");
    return;
  }
  if( ability.target != Target::Yes &&
      ability.trigger != Trigger::None ) {
    textDisplayMassage("This ability doesn't need a target or activated by trigger.");
    return;
  }
  if ( ability.ability == Ability::AtkDef ) {
    if(!exist_minions(t, p)) {
      textDisplayMassage("The minions doesn't exist.");
      return;
    }
    minions[index][i].setAction(minions[index][i].getAction() - 1);
    players[index].setMana(players[index].getMana() - ability.cost);
    AtkDef(t, p, ability.num1, ability.num2);
  }
}

void Board::play(const int &target) {
  const int index = turn % 2;
  const int oppoent_index = (turn + 1) % 2;
  if(!players[index].exist_hand(target)) return;
  std::string new_card = players[index].useHand(target);
  //std::cout <<  new_card << std::endl; //for_test
  if( new_card == "" ) {
    //players[index].addHand(new_card);
    return;
  }
  std::string type =  whatType(new_card);
  if( type == "Minion" )  {
    Minion new_minion = createMinion(new_card);
    if( new_minion.getCost() <= players[index].getMana()) {
      if( minions[index].size() < 5 ) {
        players[index].setMana(players[index].getMana() - new_minion.getCost());
        minions[index].emplace_back(new_minion);
        players[index].discard(target);
        #if 1 //for_test
        int new_minion_i = minions[index].size() - 1;
        checkTrigger(Trigger::OwnSummon, index, index, new_minion_i); //checkTrigger
        checkTrigger(Trigger::OppoentSummon, oppoent_index, index, new_minion_i);
        checkTrigger(Trigger::Summon, oppoent_index, index, new_minion_i);
        checkTrigger(Trigger::Summon, index, index, new_minion_i);
        #endif
      } else {
        //players[index].addHand(new_card);
        textDisplayMassage("The slots are full.");
      }
    } else {
      //players[index].addHand(new_card);
      textDisplayMassage("No enough mana.");
    }
  } else if ( type == "Spell" ) {
    Spell new_spell = createSpell(new_card);
    Effect new_ability = new_spell.getEffects().back();
    if( new_ability.cost <= players[index].getMana() &&
        new_ability.target == Target::No &&
        new_ability.trigger == Trigger::None ) {
      if( new_ability.ability == Ability::Charge ) {
        if(rituals[index].getName() != "") {
          players[index].discard(target);
          players[index].setMana(players[index].getMana() - new_ability.cost);
          recharge(new_ability.num1);
        } else {
          //players[index].addHand(new_card);
          textDisplayMassage("Need a ritual.");
        }
      } else if ( new_ability.ability == Ability::Resurrect ) {
        if(minions[index].size() < 5) {
          resurrect();
          players[index].discard(target);
          players[index].setMana(players[index].getMana() - new_ability.cost);
        } else {
          //players[index].addHand(new_card);
          textDisplayMassage("The slots are full.");
        }
      } else if ( new_ability.ability == Ability::AtkDef) {
        for(int i = minions[oppoent_index].size()-1; i >= 0; i--) {
          AtkDef(i, oppoent_index, new_ability.num1, new_ability.num2);
        }
        for(int i = minions[index].size()-1; i >= 0; i--) {
          AtkDef(i, index, new_ability.num1, new_ability.num2);
        }
        players[index].setMana(players[index].getMana() - new_ability.cost);
        players[index].discard(target);
      }
    } else {
      //players[index].addHand(new_card);
      textDisplayMassage("No enough mana our or need a target");
    }
  } else if (type == "Ritual" ) {
    Ritual new_ritual = createRitual(new_card);
    if( new_ritual.getCost() <= players[index].getMana()) {
      players[index].setMana(players[index].getMana() - new_ritual.getCost());
      players[index].discard(target);
      rituals[index] = new_ritual;
    } else {
      //players[index].addHand(new_card);
      textDisplayMassage("No enough Mana");
    }
  }
}

void Board::play(const int &i, const int &p, const int &t) {
  //std::cout << "play 3 arguments" << std::endl; //for_test
  const int index = turn % 2; //exist_hand
  if(!players[index].exist_hand(i)) return;
  std::string new_card = players[index].useHand(i);
  if( new_card == "" ) {
    textDisplayMassage("Can't find this handcard.");
    //players[index].addHand(new_card);
    return;
  }
  std::string type =  whatType(new_card);
  if( type == "Spell" ) {
    Spell new_spell = createSpell(new_card);
    Effect new_ability = new_spell.getEffects().back();
    if( players[index].getMana() < new_ability.cost ) {
      //players[index].addHand(new_card);
      textDisplayMassage("No enough Mana");
      return;
    }
    if (new_ability.target != Target::Yes &&
        new_ability.trigger != Trigger::None ) {
      //players[index].addHand(new_card);
      textDisplayMassage("This spell doesn't need a target or a trigger.");
      return;
    }
    if( new_ability.target == Target::Yes) {
      if (new_ability.ability == Ability::AtkDef) {
        if(exist_minions(t, p)) {
          players[index].discard(i);
          players[index].setMana(players[index].getMana() - new_ability.cost);
          AtkDef(t, p, new_ability.num1, new_ability.num2);
        } else {
          //players[index].addHand(new_card);
          textDisplayMassage("The target does not exist");
        }
      } else if (new_ability.ability == Ability::Unsummon) {
        if(exist_minions(t, p)) {
          players[index].discard(i);
          players[index].setMana(players[index].getMana() - new_ability.cost);
          unsummon(t, p);
        } else {
          //players[index].addHand(new_card);
          textDisplayMassage("The target does not exist");
        }
      } else if (new_ability.ability == Ability::Disenchant) {
        if(exist_minions(t, p)) {
          players[index].discard(i);
          players[index].setMana(players[index].getMana() - new_ability.cost);
          minions[p][t].popEnchantment();
        } else {
          //players[index].addHand(new_card);
          textDisplayMassage("The target does not exist");
        }
      } else if (new_ability.ability == Ability::Destory) {
        if (t == 5) {
          if(rituals[p].getName() != "") {
            players[index].discard(i);
            players[index].setMana(players[index].getMana() - new_ability.cost);
            destory(t, p);
          } else {
            //players[index].addHand(new_card);
            textDisplayMassage("No ritual to be destory");
          }
        } else {
          if(exist_minions(t, p)) {
            players[index].discard(i);
            players[index].setMana(players[index].getMana() - new_ability.cost);
            destory(t, p);
          } else {
            //players[index].addHand(new_card);
            textDisplayMassage("No minion to be destory");
          }
        }
      } else if(new_ability.ability == Ability::Charge) {
        if(t != 5) {
          textDisplayMassage("Target should be a rutial");
          return;
        }
        players[index].discard(i);
        players[index].setMana(players[index].getMana() - new_ability.cost);
        recharge(new_ability.num1);
      } else {
        //players[index].addHand(new_card);
        textDisplayMassage("Erro, no this effect");
      }
    } else {
      //players[index].addHand(new_card);
      textDisplayMassage("This spell do not need a specific target.");
    }
    } else if (type == "Enchantment") {
    Enchantment new_enchantment = createEchantment(new_card);
    Effect new_ability = new_enchantment.getEffects().back();
    if( players[index].getMana() < new_enchantment.getCost() ) {
      //players[index].addHand(new_card);
      textDisplayMassage("No enough Mana");
      return;
    }
    if(!exist_minions(t, p)) {
      //players[index].addHand(new_card);
      textDisplayMassage("THe minion doesn't exist");
      return;
    }
    players[index].discard(i);
    players[index].setMana( players[index].getMana() - new_enchantment.getCost() );
    minions[p][t].addEnchantment(new_enchantment);
  } else {
    //players[index].addHand(new_card);
    textDisplayMassage("Following the rules, only spell and enchantments can be played to a specific target.");
  }
}

bool Board::is_need_target_play(const int & t) {
  const int index = turn % 2;
  if(!players[index].exist_hand(t)) return false;
  std::string new_card = players[index].useHand(t);
  std::string type =  whatType(new_card);
  bool rv = false;
  if( type == "Spell") {
    if(createSpell(new_card).getEffects().back().target == Target::Yes) {
      rv = true;
    }
  } else if ( type == "Enchantment") {
    rv = true;
  }
  //players[index].addHand(new_card);
  return rv;
}

bool Board::is_need_target_use(const int & t) {
  const int index = turn % 2;
  if(!exist_minions(t, index)) {
    return false;
  }
  if(minions[index][t].getEffects().back().target == Target::Yes) {
    return true;
  } else {
    return false;
  }
}

void Board::set_player_name(const int &p, std::string name) {
  players[p].setName(name);
}

void Board::end() {
  #if 1 //for_test
  checkTrigger(Trigger::OwnEnd);
  checkTrigger(Trigger::OppoentEnd);
  checkTrigger(Trigger::End);
  #endif
  turn++;
  for(int i = 0; i < minions[turn % 2].size(); i ++) {
    minions[turn % 2][i].setAction(minions[turn % 2][i].getAction() + 1);
  }
  players[turn % 2].restoreMana();
  players[turn % 2].draw();
  #if 1 //for_test
  checkTrigger(Trigger::OwnStart);
  checkTrigger(Trigger::OppoentStart);
  checkTrigger(Trigger::Start);
  #endif
}

void Board::draw() {
  if(is_test) {
    players[turn % 2].draw();
  }
}

void Board::discard(const int &i) {
  if(is_test && players[turn % 2].exist_hand(i)) {
    players[turn % 2].discard(i);
  }
}

//for display
void Board::checkTrigger(const Trigger &trigger, const int &index, const int & p, const int & t) {
  //std::cout << "checkTrigger 3" << std::endl; //for_test
  for(int i =  minions[index].size() - 1; i >= -1; i--) {
    bool is_ritual = (i == -1);
    Effect ability;
    if(is_ritual) {
      if(rituals[index].getName() == "") continue;
      ability = rituals[index].getEffects().back();
      if(ability.cost > rituals[index].getCharge()) continue;
    } else {
      ability = minions[index][i].getEffects().back();
    }
    //std::cout << i <<std::endl; //for_test
    if(ability.trigger == trigger && ability.is_scilence == false) {
      if(ability.ability == Ability::AtkDef) {
        //std::cout<< "atk def no target" << std::endl;
        if (ability.target == Target::No) {
          for(int j= 0; j < minions[p].size(); j ++) {
            AtkDef(j, p, ability.num1, ability.num2);
          }
          if(is_ritual && rituals[index].getName() != "") {
            rituals[index].setCharge(rituals[index].getCharge() - ability.cost);
          }
        } else if (ability.target == Target::Yes) {
          AtkDef(t, p, ability.num1, ability.num2);
          if(is_ritual && rituals[index].getName() != "") {
            rituals[index].setCharge(rituals[index].getCharge() - ability.cost);
          }
        }
      } else if (ability.ability == Ability::HealthMana) {
        if(ability.target == Target::Yes){
          HealthMana(p, ability.num1, ability.num2);
          if(is_ritual && rituals[index].getName() != "") {
            rituals[index].setCharge(rituals[index].getCharge() - ability.cost);
          }
        }
      } else if (ability.ability == Ability::Destory) {
        if(ability.target == Target::Yes) {
          destory(t, p);
          if(is_ritual && rituals[index].getName() != "") {
            rituals[index].setCharge(rituals[index].getCharge() - ability.cost);
          }
        }
      }
    }
  }
}

void Board::checkTrigger(const Trigger &trigger) {
  if(trigger == Trigger::Start || trigger == Trigger::End) {
    checkTrigger(trigger, turn % 2, turn % 2);
    checkTrigger(trigger, (turn + 1) % 2, turn % 2);
  } else if (trigger == Trigger::OwnStart || trigger == Trigger::OwnEnd) {
    //std::cout << "own start check" << std::endl; //for_test
    checkTrigger(trigger, turn % 2, turn % 2);
  } else if (trigger == Trigger::OppoentStart || trigger == Trigger::OppoentEnd) {
    checkTrigger(trigger, (turn + 1) % 2, turn % 2);
  }
}

int Board::checkWinner() {
  if(players[0].getHealth() <= 0) return 1;
  if(players[1].getHealth() <= 0) return 0;
  return 2;
}


std::string Board::getGraveyard(const int &player)  {
  return players[player].getGraveyard();
}

std::vector<std::string> Board::getHand(const int &player){
  return players[player].discribeHand();
}

InfoDisplay Board::getRitual(const int &player){
    InfoDisplay the_ritual = ritual_to_info(rituals[player]);
    return the_ritual;
}



std::vector<InfoDisplay> Board::getMinions(const int &player){
    int minions_size = minions[player].size();
    std::vector <InfoDisplay> infos;
    for (int i = 0; i< minions_size; i++){
        InfoDisplay the_minion = minion_to_info(minions[player][i]);
        infos.emplace_back(the_minion);
    }
    return infos;
}

InfoDisplay Board::ritual_to_info(Ritual ritual){
    InfoDisplay info;
    if (ritual.getName() == "") {
      info.name = "NoneRitual";
      info.cost=0;
      info.type= "ritual";
      info.atk=0;
      info.def=0;
      info.desc="";
      info.ability_cost=0;
      info.charge=0;
      info.ability = "";
      info.enchant_atk = "";
      info.enchant_def= "";
    }else{
      info.name = ritual.getName();
      info.cost = ritual.getCost();
      info.type = "ritual";
      info.atk= -1;
      info.def= -1;
      std::vector<Effect> effects = ritual.getEffects();
      Effect effect = effects.back();
      info.desc = effect.describe;
      info.ability_cost = effect.cost;
      info.charge = ritual.getCharge();
      info.ability = "";
      info.enchant_def = "";
      info.enchant_atk = "";
    }
    return info;
}

InfoDisplay Board::minion_to_info(Minion minion){
    InfoDisplay info;
    info.name = minion.getName();
    info.cost = minion.getCost();
    info.type = "minion";
    info.atk = minion.getAtk();
    info.def = minion.getDef();
    std::vector<Effect> effects = minion.getEffects();
    Effect effect = effects.back();
    info.desc = effect.describe;
    info.charge = -1;
    if (info.name == "Earth Elemental"||info.name == "Air Elemental"){
        info.ability = "none";
    }else if (effect.ability != Ability::None
              && effect.trigger == Trigger::None){
        info.ability = "activated";
    }else{
        info.ability = "triggered";
    }
    if (effect.cost == 0){
        info.ability_cost = -1;
    }else{
        info.ability_cost = effect.cost;
    }
    info.enchant_def = "";
    info.enchant_atk = "";
    return info;
}

std::vector<std::string> Board::inspectMinion(const int &player,
                                              const int &target,
                                              InfoDisplay &minion_info){
    Minion minion = minions[player][target];
    std::vector<Enchantment> enchat = minion.getEnchantments();
    minion_info.name=minion.getName();
    minion_info.cost=minion.getCost();
    minion_info.atk=minion.getAtk();
    minion_info.def=minion.getDef();
    if (minion.getEffects().back().ability == Ability::None) minion_info.ability="none";
    else if (minion.getEffects().back().trigger!=Trigger::None) {
      minion_info.ability="triggered";
      minion_info.desc=minion.getEffects().back().describe;
    }
    else {
      minion_info.ability="activated";
      minion_info.desc=minion.getEffects().back().describe;
      minion_info.ability_cost=minion.getEffects().back().cost;
    }
    std::vector<std::string> enchants;
    for (int i = 0; i < enchat.size(); i++){
        std::string name = enchat[i].getName();
        enchants.emplace_back(name);
    }
    return enchants;
}


std::string Board::getPlayer(const int &player, int &mana, int &health){
    std::string name = players[player].getname();
    mana = players[player].getMana();
    health = players[player].getHealth();
    return name;
}

//for_test
#if 0
void Board::print_board() {
  std::cout << "player 1: "<< players[0].getname() << " Health: "
  << players[0].getHealth() << " Mana: " << players[0].getMana() << std::endl;
  for(int i = 0; i < minions[0].size(); i++) {
    std::cout << minions[0][i].getName() << " atk:" << minions[0][i].getAtk()
    << " def:" << minions[0][i].getDef() << std::endl;
  }
  std::cout << "player 2: "<< players[1].getname() << " Health: "
   << players[1].getHealth() << " Mana: "  << players[1].getMana() << std::endl;
  for(int i = 0; i< minions[1].size(); i++) {
    std::cout << minions[1][i].getName()<< " atk:"<< minions[1][i].getAtk()
    << " def:" << minions[1][i].getDef() << std::endl;
  }
}
#endif
