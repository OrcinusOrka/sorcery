#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_
#include <string>
#include <iostream>
#include <vector>
#include "ascii_graphics.h"
#include "infodisplay.h"
#include "board.h"

class TextDisplay {
	Board &bp;
  std::vector<InfoDisplay> allCards= {
   {"Air Elemental",0,"minion",1,1,"",-1,-1,"none","",""},
   {"Earth Elemental",3,"minion",4,4,"",-1,-1,"none","",""},
   {"Fire Elemental",2,"minion",2,2,
    "Whenever an opponent's minion enters play, deal 1 damage to it.",-1,
    -1,"triggered","",""},
   {"Potion Seller",2,"minion",1,3,
    "At the end of your turn, all your monions gain +0/+1.",
    -1,-1,"triggered","",""},
   {"Novice Pyromancer",1,"minion",0,1,
    "Deal 1 damage to target minion",1,-1,"activated","",""},
   {"Apprentice Summoner",1,"minion",1,1,"Summon a 1/1 air elemental",
    1,-1,"activated","",""},
   {"Master Summoner",3,"minion",2,3,
    "Summon up to three 1/1 air elementals",2,-1,"activated","",""},
   {"Banish",2,"spell",-1,-1,"Destroy target minion or ritual",
    -1,-1,"","",""},
   {"Unsummon",1,"spell",-1,-1,"Return target minion to its owner's hand",
    -1,-1,"","",""},
   {"Recharge",1,"spell",-1,-1,"Your ritual gains 3 charges",
    -1,-1,"","",""},
   {"Disenchant",1,"spell",-1,-1,
    "Destroy the top enchantment on target minion",-1,-1,"","",""},
   {"Raise Dead",1,"spell",-1,-1,
    "Resurrect the top minion in your graveyard",-1,-1,"","",""},
   {"Blizzard",3,"spell",-1,-1,"Deal 2 damage to all minions",
    -1,-1,"","",""},
   {"Giant Strength",1,"enchant_atk_def",-1,-1,"",-1,-1,"","+2","+2"},
   {"Magic Fatigue",0,"enchant",-1,-1,
    "Enchanted minion's activated ability costs 2 more",-1,-1,"","",""},
   {"Silence",1,"enchant",-1,-1,"Enchanted minion cannot use abilities",
    -1,-1,"","",""},
   {"Dark Ritual",0,"ritual",-1,-1,"At the start of your turn, gain 1 mana",
    1,5,"","","" },
   {"Aura of Power",1,"ritual",-1,-1,
    "Whenever a minion enters play under your control, it gains +1/+1",
    1,4,"","",""},
   {"Standstill",3,"ritual",-1,-1,
    "Whenever a minion enters play, destroy it",2,4,"","",""},
   {"NoneRitual",0,"",0,0,"",0,0,"","",""}
  };


  const std::string up_down = EXTERNAL_BORDER_CHAR_UP_DOWN;
  const std::string left_right = EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
  const std::string top_left = EXTERNAL_BORDER_CHAR_TOP_LEFT;
  const std::string top_right = EXTERNAL_BORDER_CHAR_TOP_RIGHT;
  const std::string bottom_left = EXTERNAL_BORDER_CHAR_BOTTOM_LEFT;
  const std::string bottom_right = EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT;
  std::vector<std::string> empty_spot=CARD_TEMPLATE_EMPTY;
  std::vector<std::string> card_border=CARD_TEMPLATE_BORDER;

  std::vector<std::string> card1;
  std::vector<std::string> card2;
  std::vector<std::string> card3;
  std::vector<std::string> card4;
  std::vector<std::string> card5;

  //const int width=165; // the width of the board
  const int card_width=33; // the width of a card

  card_template_t what_card(std::string name);
  card_template_t info_to_print(InfoDisplay info);
	std::vector<std::string> set_board();
  std::vector<std::string> set_hand(int which_player);
  std::vector<std::string> set_inspect(int which_player, int target);

  public:
	TextDisplay(Board &bp);
  void display(std::string type, int which_player, int target);
	void print_commond_list();
};


#endif
