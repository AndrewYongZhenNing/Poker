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
  int evaluate(std::vector<Card> hand); // [to be used in method evaluate, from Hand class] evaluates the points of each player's hand, returns an integer (the score)
  void flush_check(std::vector<Card> hand);
  void straight_flush_check(std::vector<Card> hand);

protected:

  std::vector<Card> _hand;
  std::vector<Card> _temp_player; // create a temporary Player object to take player's pocket cards
  std::vector<Card>::iterator _temp_iter;
  int pair = 0;
  bool three_kind = false;
  bool four_kind = false;
  bool flush = false;
  bool straight = false;
  bool straight_flush = false;

  //save below for full Poker game, where ranks are compared, now focus on finding winner by assigning players with a number for whatever rank they get and if it is the same call draw
  // std::vector<Card> _high_card;
  // std::vector<Card> _pair;


};

#endif
