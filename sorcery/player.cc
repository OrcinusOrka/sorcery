#include "player.h"
#include <iostream>

void Player::init(std::string filename, bool is_test, const int &seed) {
    name = "";
    deck.init(filename);
    if(is_test) {
      mana = 100; //for_test
      health = 7; //for_test
    } else {
      deck.shuffle(seed);
      mana = 3;
      health = 20;
    }
    handcards.clear();
    graveyard.clear();
    for (int i = 0; i < 4; i++){
      std::string cards;
      cards = deck.getTop();
      handcards.emplace_back(cards);
    }
}

void Player::toGraveyard(std::string str) {
    graveyard.emplace_back(str);
}

std::string Player::getGraveyard() {
  std::string r = "";
  if(graveyard.size() > 0) {
    r = graveyard.back();
  }
  return r;
}

void Player::rm_graveyard() {
  if(graveyard.size() > 0) {
    graveyard.pop_back();
  }
}

void Player::draw() {
  if(handcards.size() < 5 && !deck.isEmpty() ) {
    std::string s = deck.getTop();
    handcards.push_back(s);
  }
}

void Player::setName(const std::string& s) {
  name = s;
}

std::string Player::getname() const{
  return name;
}

void Player::discard(const int &n){
  for(int i = n; i< handcards.size()-1 ;i++){
    handcards[i] = handcards[i+1];
  }
  handcards.pop_back();
  //std::cout << handcards.size() << std::endl; //fot_test
}


std::vector<std::string> Player::discribeHand(){
  return handcards;
}

int Player::getMana() const {
  return mana;
}

void Player::setMana(const int &n) {
  mana = n;
}

void Player::restoreMana() {
  mana = mana + 1;
}

int Player::getHealth() const {
  return health;
}

void Player::setHealth(const int &n) {
  health = n;
  validHealth();
}

void Player::validHealth() {
  if( health < 0 ) {
    health = 0;
  }
}

void Player::addHand(const std::string &card) {
  if(handcards.size() < 5){
    handcards.emplace_back(card);
  }
}

std::string Player::useHand(const int &i) {
  std::string rv = "";
  if(handcards.size() > 0 && i < handcards.size()) {
    rv = handcards[i];
  }
  return rv;
}

bool Player::exist_hand(const int &i) {
  if(i < handcards.size() && i >= 0) return true;
  else return false;
}

Player::~Player() {}
