#include "deck.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

void Deck::init(std::string filename){
    std::ifstream file_s{filename};
    std::string s = "";
    while(!file_s.eof() && getline(file_s, s)) {
        cards.emplace_back(s);
    }
}

std::string Deck::getTop(){
    std::string return_value;
    return_value = cards.back();
    cards.pop_back();
    return return_value;
}

bool Deck::isEmpty(){
    if (cards.size() == 0){
        return true;
    }else{
        return false;
    }
}

void Deck::putBack(std::string s){
    cards.push_back(s);
}

void Deck::shuffle(const int &seed) {
  srand(seed);
  std::string tmp = "default";
  for(int i = 0; i < 100 ; i++) {
    int j = rand() % cards.size();
    int k = rand() % cards.size();
    tmp = cards[j];
    cards[j] = cards[k];
    cards[k] = tmp;
  }
}
