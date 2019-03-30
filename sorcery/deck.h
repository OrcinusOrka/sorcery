#ifndef _DECK_H_
#define _DECK_H_

#include <vector>
#include <string>

class Deck{
    std::vector<std::string> cards;
public:
    void init(std::string filename);
    std::string getTop();
    bool isEmpty();
    void putBack(std::string);
    void shuffle(const int &seed);
};

#endif
