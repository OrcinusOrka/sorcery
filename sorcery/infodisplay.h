#ifndef _INFODISPLAY_H_
#define _INFODISPLAY_H_
#include <string>

struct InfoDisplay {
  std::string name;
  int cost;
  std::string type; // minion, ritual, spell, enchant_atk_def, enchant
  int atk;
  int def;
  std::string desc; // any desc
  int ability_cost; // any other cost
  int charge; // for ritual
//  int player_n;  // may not need to use
  std::string ability; // what ability: triggered, activated, none
  std::string enchant_atk;
  std::string enchant_def;
};

#endif
