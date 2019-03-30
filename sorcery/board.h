#ifndef _BOARD_H_
#define _BOARD_H_

#include <iostream>
#include <vector>
#include <string>
#include "player.h"
#include "minion.h"
#include "ritual.h"
#include "spell.h"
#include "effect.h"
#include "infodisplay.h"

class Board{
    std::vector<Player> players;
    std::vector<std::vector<Minion>> minions;
    std::vector<Ritual> rituals;
    int turn = 0; //start with zero
    bool is_test = false;

    bool exist_minions(const int &target, const int &i);
    void setDef(const int &target, const int &i, const int &new_def);
    void minionDie(const int &target, const int &i);
    void textDisplayMassage(const std::string & message);

    //ablities
    void HealthMana(const int &index, const int &health_num, const int &mana_num);
    void destory(const int &target, const int &index); //get from 0 to 5, 5 represent ritual
    void AtkDef(const int &target, const int &index,
                const int &atk_num, const int &def_num);
    void unsummon(const int &target, const int &index);
    void recharge(const int &charge_num);
    void disenchant(const int &target);
    void resurrect();
    void minionsAblityCostMore(const int &target, const int &num);
    void summon(std::string summonMonster, const int &num = 1); //num represent how many mins you want to summon

    //for Display
    InfoDisplay minion_to_info(Minion minion);
    InfoDisplay ritual_to_info(Ritual ritual);

    //create cards
    std::string whatType(std::string card);
    Minion createMinion(std::string new_card);
    Spell createSpell(std::string new_card);
    Enchantment createEchantment(std::string new_card);
    Ritual createRitual(std::string new_card);

    void checkTrigger(const Trigger &trigger); //needs more work
    void checkTrigger(const Trigger &trigger, const int &index, const int & p, const int & t = -1);

 public:
    int checkWinner(); //0: player1, 1: player2, otherwise: no player
    void init(const std::string &deck1, const std::string &deck2);
    void testMode();
    void attack(const int &target);
    void attack(const int &subject, const int &object);
    void use(const int &target);
    void use(const int &i, const int &p, const int &t); //5 represent ritual
    void play(const int &target);
    void play(const int &i, const int &p, const int &t); //5 represent ritual
    bool is_need_target_play(const int & t);
    bool is_need_target_use(const int & t);
    void set_player_name(const int &p, std::string name);
    void end();
    //only can be run in test modle
    void draw();
    void discard(const int &i);
    void print_board();


    //for TextDisplay
    //0 represent player1, 0 represent minion_1

    std::string getGraveyard(const int &player);
    std::vector<std::string> getHand(const int &player);
    InfoDisplay getRitual(const int &player);
    std::vector<InfoDisplay> getMinions(const int &player);
    std::vector<std::string> inspectMinion(const int &player,
                                                  const int &target,
                                                  InfoDisplay &minion_info);
    std::string getPlayer(const int &player, int &mana, int &health);
};

#endif /* _BOARD_H_ */
