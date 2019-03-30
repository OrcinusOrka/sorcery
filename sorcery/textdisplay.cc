#include "textdisplay.h"
#include "ascii_graphics.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;


// helper
card_template_t TextDisplay::what_card(string name) {
  int index=0;
  for(int i=0; i<allCards.size(); ++i) {
    if (allCards[i].name==name) {
      index=i;
      break;
    }
  }
  int cost = allCards[index].cost;
  string type = allCards[index].type;
  int atk = allCards[index].atk;
  int def = allCards[index].def;
  string desc = allCards[index].desc;
  int ability_cost = allCards[index].ability_cost;
  int charge = allCards[index].charge;
  string ability = allCards[index].ability;
  string enchant_atk = allCards[index].enchant_atk;
  string enchant_def = allCards[index].enchant_def;

  if (type=="minion" && ability=="none") {
    return display_minion_no_ability(name,cost,atk,def);
  }
  if (type=="minion" && ability=="triggered") {
    return display_minion_triggered_ability(name,cost,atk,def,desc);
  }
  if (type=="minion" && ability=="activated") {
    return display_minion_activated_ability(name,cost,atk,def,
           ability_cost,desc);
  }
  if (type=="ritual") {
    return display_ritual(name,cost,ability_cost,desc,charge);
  }
  if (type=="spell") {
    return display_spell(name,cost,desc);
  }
  if (type=="enchant_atk_def") {
    return display_enchantment_attack_defence(name,cost,desc,enchant_atk,
           enchant_def);
  }
  if (type=="enchant") {
    return display_enchantment(name,cost,desc);
  }
  return card_border;
}

// helper for changing ritual and minion
card_template_t TextDisplay::info_to_print(InfoDisplay info) {
  string name=info.name;
  string type=info.type;
  string ability=info.ability;
  int cost=info.cost;
  int atk=info.atk;
  int def=info.def;
  string desc=info.desc;
  int ability_cost=info.ability_cost;
  int charge=info.charge;
  if (type=="minion" && ability=="none") {
    return display_minion_no_ability(name,cost,atk,def);
  }
  if (type=="minion" && ability=="triggered") {
    return display_minion_triggered_ability(name,cost,atk,def,desc);
  }
  if (type=="minion" && ability=="activated") {
    return display_minion_activated_ability(name,cost,atk,def,
           ability_cost,desc);
  }
  if (type=="ritual") {
    return display_ritual(name,cost,ability_cost,desc,charge);
  }
}


vector<string> TextDisplay::set_board() {
  vector<string> board;
  string top="";
  string bottom="";

  top+=top_left;
  for(int i=0; i<card_width*5; ++i) top+=left_right;
  top+=top_right;

  bottom+=bottom_left;
  for(int i=0; i<card_width*5; ++i) bottom+=left_right;
  bottom+=bottom_right;

  board.emplace_back(top);

  vector<string> ritual;
  string player_name;
  vector<string> player;
  string grave_name;
  vector<string> graveyard;
  vector<InfoDisplay> minion_infos;

  // for player1
  InfoDisplay r=bp.getRitual(0);
  if (r.name=="NoneRitual") ritual=card_border;
  else ritual=info_to_print(r);
  //ritual=card_border; //
  int life;
  int mana;
  player_name=bp.getPlayer(0,mana,life);
 // player_name="Sean"; //
 // life=20; //
 // mana=0;  //
  player=display_player_card(1, player_name, life, mana);
  grave_name=bp.getGraveyard(0);
  //grave_name="Air Elemental"; //
  if (grave_name=="") graveyard=card_border;
  else graveyard=what_card(grave_name);


  card1=ritual;
  card2=empty_spot;
  card3=player;
  card4=empty_spot;
  card5=graveyard;

  for(int i=0; i<card1.size(); ++i) {
    board.emplace_back(up_down+card1[i]+card2[i]+card3[i]+card4[i]+card5[i]
                       +up_down);
  }

  minion_infos=bp.getMinions(0);
//  minion_infos={{"Novice Pyromancer",1,"minion",4,8,"deal",3,0,"activated","",""},{"Potion Seller",2,"minion",1,4,"hhh",0,0,"triggered","",""},
 // {"Earth Elemental",3,"minion",4,5,"",0,0,"none","",""}};
  if (minion_infos.empty()) {
    card1=card_border;
    card2=card_border;
    card3=card_border;
    card4=card_border;
    card5=card_border;
  }
  else if (minion_infos.size()==1) {
    card1=info_to_print(minion_infos[0]);
    card2=card_border;
    card3=card_border;
    card4=card_border;
    card5=card_border;
  }
  else if (minion_infos.size()==2) {
    card1=info_to_print(minion_infos[0]);
    card2=info_to_print(minion_infos[1]);
    card3=card_border;
    card4=card_border;
    card5=card_border;
  }
  else if (minion_infos.size()==3) {
    card1=info_to_print(minion_infos[0]);
    card2=info_to_print(minion_infos[1]);
    card3=info_to_print(minion_infos[2]);
    card4=card_border;
    card5=card_border;
  }
  else if (minion_infos.size()==4) {
    card1=info_to_print(minion_infos[0]);
    card2=info_to_print(minion_infos[1]);
    card3=info_to_print(minion_infos[2]);
    card4=info_to_print(minion_infos[3]);
    card5=card_border;
  }
  else if (minion_infos.size()==5) {
    card1=info_to_print(minion_infos[0]);
    card2=info_to_print(minion_infos[1]);
    card3=info_to_print(minion_infos[2]);
    card4=info_to_print(minion_infos[3]);
    card5=info_to_print(minion_infos[4]);
  }
  for(int i=0; i<card1.size(); ++i) {
    board.emplace_back(up_down+card1[i]+card2[i]+card3[i]+card4[i]+card5[i]
                       +up_down);
  }

  // print sorcery
  vector<string> center_graph=CENTRE_GRAPHIC;
  for(int i=0; i<center_graph.size(); ++i) {
    board.emplace_back( center_graph[i]);
  }

  // for player2

  minion_infos=bp.getMinions(1);
 // minion_infos={{"Air Elemental",0,"minion",1,1,"",0,0,"none","",""},
 // {"Fire Elemental",2,"minion",3,2,"hhh",0,0,"triggered","",""},
 // {"Apprentice Summoner",1,"minion",2,2,"666",1,0,"activated","",""}};
  if (minion_infos.empty()) {
    card1=card_border;
    card2=card_border;
    card3=card_border;
    card4=card_border;
    card5=card_border;
  }
  else if (minion_infos.size()==1) {
    card1=info_to_print(minion_infos[0]);
    card2=card_border;
    card3=card_border;
    card4=card_border;
    card5=card_border;
  }
  else if (minion_infos.size()==2) {
    card1=info_to_print(minion_infos[0]);
    card2=info_to_print(minion_infos[1]);
    card3=card_border;
    card4=card_border;
    card5=card_border;
  }
  else if (minion_infos.size()==3) {
    card1=info_to_print(minion_infos[0]);
    card2=info_to_print(minion_infos[1]);
    card3=info_to_print(minion_infos[2]);
    card4=card_border;
    card5=card_border;
  }
  else if (minion_infos.size()==4) {
    card1=info_to_print(minion_infos[0]);
    card2=info_to_print(minion_infos[1]);
    card3=info_to_print(minion_infos[2]);
    card4=info_to_print(minion_infos[3]);
    card5=card_border;
  }
  else if (minion_infos.size()==5) {
    card1=info_to_print(minion_infos[0]);
    card2=info_to_print(minion_infos[1]);
    card3=info_to_print(minion_infos[2]);
    card4=info_to_print(minion_infos[3]);
    card5=info_to_print(minion_infos[4]);
  }

  for(int i=0; i<card1.size(); ++i) {
    board.emplace_back(up_down+card1[i]+card2[i]+card3[i]+card4[i]+card5[i]
                       +up_down);
  }

  r=bp.getRitual(1);
  if (r.name=="NoneRitual") ritual=card_border;
  else ritual=info_to_print(r);
  player_name=bp.getPlayer(1,mana,life);
 // player_name="Ten"; //
 // life=20; //
 // mana=0; //
  player=display_player_card(2,player_name,life,mana);
  grave_name=bp.getGraveyard(1);
  if (grave_name=="") graveyard=card_border;
  else graveyard=what_card(grave_name);

  card1=ritual;
  card2=empty_spot;
  card3=player;
  card4=empty_spot;
  card5=graveyard;

  for(int i=0; i<card1.size(); ++i) {
    board.emplace_back(up_down+card1[i]+card2[i]+card3[i]+card4[i]+card5[i]
                       +up_down);
  }
  board.emplace_back(bottom);
  return board;
}






vector<string> TextDisplay::set_hand(int which_player) {
  vector<string> hand;
 // vector<string> card_names={"Silence","Potion Seller","Air Elemental","Blizzard","Aura of Power"}; //
  vector<string> card_names=bp.getHand(which_player);
  //card_names=bp.getHand(which_player);
  // set cards
  if (card_names.size()==5) {
    card1=what_card(card_names[0]);
    card2=what_card(card_names[1]);
    card3=what_card(card_names[2]);
    card4=what_card(card_names[3]);
    card5=what_card(card_names[4]);
  }
  else if (card_names.size()==4) {
    card1=what_card(card_names[0]);
    card2=what_card(card_names[1]);
    card3=what_card(card_names[2]);
    card4=what_card(card_names[3]);
    card5=card_border;
  }
  else if (card_names.size()==3) {
    card1=what_card(card_names[0]);
    card2=what_card(card_names[1]);
    card3=what_card(card_names[2]);
    card4=card_border;
    card5=card_border;
  }
  else if (card_names.size()==2) {
    card1=what_card(card_names[0]);
    card2=what_card(card_names[1]);
    card3=card_border;
    card4=card_border;
    card5=card_border;
  }
  else if (card_names.size()==1) {
    card1=what_card(card_names[0]);
    card2=card_border;
    card3=card_border;
    card4=card_border;
    card5=card_border;
  }
  else if (card_names.empty()) {
    card1=card_border;
    card2=card_border;
    card3=card_border;
    card4=card_border;
    card5=card_border;
  }

  for(int i=0; i<card1.size(); ++i) {
    hand.emplace_back(card1[i]+card2[i]+card3[i]+card4[i]+card5[i]);
  }
  return hand;
}



vector<string> TextDisplay::set_inspect(int which_player, int target) {
  vector<string> inspect;
  InfoDisplay minion={"",0,"minion",0,0,"",0,0,"","",""};
  vector<string> enchants=bp.inspectMinion(which_player, target, minion);
 // minion={"Air Elemental",0,"minion",13,13,"",-1,-1,"none","",""}; //
//  enchants={"Giant Strength", "Giant Strength","Giant Strength","Giant Strength","Giant Strength","Silence"}; //
  vector<string> print_minion;
  string name=minion.name;
  int cost=minion.cost;
  int atk=minion.atk;
  int def=minion.def;
  string desc=minion.desc;
  int ability_cost=minion.ability_cost;

  if (minion.ability=="none") {
    print_minion=display_minion_no_ability(name,cost,atk,def);
  }
  if (minion.ability=="triggered") {
    print_minion=display_minion_triggered_ability(name,cost,atk,def,desc);
  }
  if (minion.ability=="activated") {
    print_minion=display_minion_activated_ability(name,cost,atk,def,
                 ability_cost,desc);
  }
  // print minion
  for(int i=0; i<print_minion.size(); ++i) {
    inspect.emplace_back(print_minion[i]);
  }

  if (enchants.empty()) return inspect;

  int int_line_num=enchants.size()/5;
  int remain=enchants.size()%5;

  for(int i=0; i<int_line_num; i+=5) {
    card1=what_card(enchants[i]);
    card2=what_card(enchants[i+1]);
    card3=what_card(enchants[i+2]);
    card4=what_card(enchants[i+3]);
    card5=what_card(enchants[i+4]);
    for(int i=0; i<card1.size(); ++i) {
      inspect.emplace_back(card1[i]+card2[i]+card3[i]+card4[i]+card5[i]);
    }
  }
  // dealing with the remaining enchants
  int remain_index=int_line_num*5;
  if (remain==1) {
    card1=what_card(enchants[remain_index]);
    for(int i=0; i<card1.size(); ++i) {
      inspect.emplace_back(card1[i]);
    }
  }
  else if (remain==2) {
    card1=what_card(enchants[remain_index]);
    card2=what_card(enchants[remain_index+1]);
    for(int i=0; i<card1.size(); ++i) {
      inspect.emplace_back(card1[i]+card2[i]);
    }
  }
  else if (remain==3) {
    card1=what_card(enchants[remain_index]);
    card2=what_card(enchants[remain_index+1]);
    card3=what_card(enchants[remain_index+2]);
    for(int i=0; i<card1.size(); ++i) {
      inspect.emplace_back(card1[i]+card2[i]+card3[i]);
    }
  }
  else if (remain==4) {
    card1=what_card(enchants[remain_index]);
    card2=what_card(enchants[remain_index+1]);
    card3=what_card(enchants[remain_index+2]);
    card4=what_card(enchants[remain_index+3]);
    for(int i=0; i<card1.size(); ++i) {
      inspect.emplace_back(card1[i]+card2[i]+card3[i]+card4[i]);
    }
  }
  return inspect;
}

void TextDisplay::display(string type, int which_player, int target) {
  vector<string> print_item;
  if (type=="board") {
    print_item=set_board(); //
  }
  else if (type=="hand") {
    print_item=set_hand(which_player);
  }
  else if (type=="inspect") {
    print_item=set_inspect(which_player, target);
  }
  else {
    cout << "Display Options: Board, Hand, Inspect. Try again." << endl;
  }
  for(int i=0; i<print_item.size(); ++i) {
    cout << print_item[i] << endl;
  }
}

void TextDisplay::print_commond_list() {
  cout << "Commands: help -- Display this message." << endl;
  cout << "end -- End the current player's turn." << endl;
  cout << "quit -- End the game." << endl;
  cout << "attack minion other-minion -- Orders minion to attack other-minion." << endl;
  cout << "attack minion -- Orders minion to attack the opponent." << endl;
  cout << "play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player." << endl;
  cout << "use minion [target-player target-card] -- Use minion's special ability, optionally targeting target-card owned by target-player." << endl;
  cout << "inspect minion -- View a minion's card and all enchantments on that minion." << endl;
  cout << "hand -- Describe all cards in your hand." << endl;
  cout << "board -- Describe all cards on the board." << endl;
}

TextDisplay::TextDisplay(Board &bp):
  bp{bp} {}
