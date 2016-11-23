#ifndef _PLAYER_KLASS_
#define _PLAYER_KLASS_

//Relevant libraries
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

//Relevant class header files
#include "card.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PLAYER CLASS

class Player{ // creates new Player (objects)

public:
  Player();
  ~Player();
  void show_name();
  // void show_pocket(); // reveals the pocket card of the Player
  void deal(Card &top_card); //dereferences the Deck iter into the _pocket_cards container
  std::vector<Card> get_pocket(); // gets a vector container full of Card objects

protected:
  std::string player_name;
  std::vector<Card> _pocket_cards; // container with two spaces to hold the cards
  std::vector<Card>::iterator _pocket_iter; // maybe redundant

};

#endif
