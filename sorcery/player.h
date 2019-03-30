#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <vector>
#include <string>
#include "deck.h"

class Player{
    std::string name = "";
    int health = 20;
    int mana = 3;
    //int turn = 0;
    std::vector<std::string> handcards;
    Deck deck;
    std::vector<std::string> graveyard;
    void validHealth();
public:
    void init(std::string filename, bool is_test, const int &seed);
    void toGraveyard(std::string);
    std::string getGraveyard();
    void draw();
    void setName(const std::string&);
    std::string getname() const;
    void discard(const int&);
    std::vector<std::string> discribeHand();
    int getMana() const;
    void setMana(const int&);
    void restoreMana();
    int getHealth() const;
    void setHealth(const int&);
    void addHand(const std::string &card);
    std::string useHand(const int &i); //if faild, it will return "".
    bool exist_hand(const int &i);
    void rm_graveyard();
    //Player();
    ~Player();
};
#endif /* player_hpp */
