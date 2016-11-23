#ifndef _HAND_KLASS_
#define _HAND_KLASS_

//Relevant libraries
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

//Relevant class header files
#include "card.h"
#include "poker.h"
#include "player.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// HAND CLASS

class Hand{ // evaluates the hands for each player at showdown

public:

  Hand(Player &player, std::vector<Card> board); // constructor takes a Player object and a vector (from Game)
  ~Hand();

protected:

  std::vector<Card> _hand;
  std::vector<Card> _temp_player; // create a temporary Player object to take player's pocket cards
  std::vector<Card>::iterator _temp_iter;

};

#endif
