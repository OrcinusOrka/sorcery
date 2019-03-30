#ifndef _EFFECT_H_
#define _EFFECT_H_

#include <string>

enum class Ability{ None,
                   HealthMana, AtkDef,
                   Unsummon, Silence, MoreCost,
                   Charge, Summon, Disenchant,
                   Resurrect, Destory};

enum class Trigger{ None,
                    Start, Summon, End,
                    OwnStart, OwnSummon, OwnEnd,
                    OppoentStart, OppoentSummon, OppoentEnd};

enum class Target{ No, Yes};

struct Effect{
  Ability ability; //for any ablities don't need number,
                 //this number should be 0
  Trigger trigger;
  Target target;
  int num1; //+atk, +health, summon_num, +charge_num
  int num2; //+def, +mana
  int cost;
  std::string describe;
  std::string summonMonster;
  bool is_scilence = false;
};
#endif
