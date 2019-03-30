#include "board.h"
#include "card.h"
#include "cardscollection.h"
#include "deck.h"
#include "effect.h"
#include "enchantment.h"
#include "minion.h"
#include "player.h"
#include "ritual.h"
#include "spell.h"
#include "textdisplay.h"
#include <fstream>
#include <exception>
#include <sstream>
#include <string>

bool valid_player(std::string str) {
    if(str == "1" || str == "2") {
      return true;
    } else {
      return false;
    }
}

bool valid_hand(std::string str) {
  if(str.size() == 1 && str[0] >= '1' && str[0] <= '5') {
    return true;
  } else {
    return false;
  }
}

bool valid_target(std::string str) {
  if ( str.size() == 1 && ( (str[0] >= '1' && str[0] <= '5') || str[0] == 'r') ) {
    return true;
  } else {
    return false;
  }
}

void playSorcery(std::istream &in, Board &bd, TextDisplay &td, int &turn) {
  std::string cmd;
  std::string s;
  if(turn == 0) std::cout << "Enter player1's name" << std::endl;
  while(!in.eof() && getline(in, cmd)) {
    #if 1  //for_test
    if(turn == 0 || turn == 1) {
       bd.set_player_name(turn, cmd);
       if(turn == 0) std::cout << "Enter player2's name" << std::endl;
       turn++;
       continue;
    }
    #endif
    std::istringstream str_s{cmd};
    std::vector<std::string> a;
    std::string target;
    std::string sub_cmd;
    int i, p, t;
    str_s >> sub_cmd;
    while(str_s >> target) {
      a.emplace_back(target);
    }
    if(sub_cmd == "help") {
      td.print_commond_list();
    }
    else if(sub_cmd == "end") {
      bd.end();
      turn++;
    } else if (sub_cmd == "quit") {
      throw "quit";
    } else if (sub_cmd == "draw") {
      bd.draw();
    } else if ( sub_cmd == "hand") {
      td.display("hand", turn%2, 0);
    } else if ( sub_cmd == "board") {
      td.display("board", 0, 0);
      //bd.print_board();  //for_test
    } else if( sub_cmd == "discard") {
      if(a.size() == 1) {
        if(valid_hand(a[0])) {
          i = a[0][0] - '1';
          bd.discard(i);
        }
      }
    } else if( sub_cmd == "use") {
      if(a.size() == 1) {
        if(valid_hand(a[0])) {
          i = a[0][0] - '1';
          bd.use(i);
        }
      } else if (a.size() == 3) {
        if(valid_hand(a[0]) && valid_player(a[1]) && valid_target(a[2])) {
          i = a[0][0] - '1';
          p = a[1][0] - '1';
          if(a[2][0] == 'r') {
            t = 5;
          } else {
            t = a[2][0] - '1';
          }
          bd.use(i, p, t);
        }
      }
    } else if ( sub_cmd == "play" ) {
      if(a.size() == 1) {
        if(valid_hand(a[0])) {
          i = a[0][0] - '1';
          bd.play(i);
        }
      } else if (a.size() == 3) {
        if(valid_hand(a[0]) && valid_player(a[1]) && valid_target(a[2])) {
          i = a[0][0] - '1';
          p = a[1][0] - '1';
          if(a[2][0] == 'r') {
            t = 5;
          } else {
            t = a[2][0] - '1';
          }
          bd.play(i, p, t);
        }
      }
    } else if ( sub_cmd == "attack" ) {
      if(a.size() == 1) {
        if(valid_hand(a[0])) {
          i = a[0][0] - '1';
          bd.attack(i);
        }
      } else if (a.size() == 2) {
        if(valid_hand(a[0]) && valid_hand(a[1])) {
          i = a[0][0] - '1';
          t = a[1][0] - '1';
          bd.attack(i, t);
        }
      }
    } else if (sub_cmd == "inspect") {
      if(a.size() == 1 && valid_hand(a[0])) {
        i = a[0][0] - '1';
        td.display("inspect", turn%2, i);
      }
    }
    if(bd.checkWinner() == 0) {
      std::cout << "player 1 win!" << std::endl;
      throw "win";
    } else if ( bd.checkWinner() == 1) {
      std::cout << "player 2 win!" << std::endl;
      throw "win";
    }
  }
}

int main(int argc, char *argv[]) {
  Board bd;
  TextDisplay td(bd);
  std::string deck1_file = "default.deck";
  std::string deck2_file = "default.deck";
  std::string init_file = "";
  bool next_deck1 = false;
  bool next_deck2 = false;
  bool next_init = false;
  for(int i = 1; i < argc; i++) {
    std::string dec = argv[i];
    if(dec == "-deck1") {
      next_deck1 = true;
    } else if (dec == "-deck2") {
      next_deck2 = true;
    } else if (dec == "-init") {
      next_init = true;
    } else if (dec == "-testing") {
      //std::cout << "testmod" << std::endl; //for_test
      bd.testMode();
    } else {
      if(next_deck1) {
        deck1_file = dec;
        next_deck1 = false;
      } else if(next_deck2) {
        deck2_file = dec;
        next_deck2 = false;
      } else if (next_init) {
         init_file = dec;
         next_init = false;
      }
    }
  }
  try {
  int turn = 0;
  bd.init(deck1_file, deck2_file);
  if(init_file != "") {
    std::ifstream f{init_file};
    playSorcery(f, bd, td, turn);
  }
  playSorcery(std::cin, bd, td, turn);
  }
  catch(char const *) {}
}
