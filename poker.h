#ifndef _POKER_KLASS_
#define _POKER_KLASS_

//Relevant libraries
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

//Relevant class header files
#include "card.h"
#include "deck.h"
#include "player.h"
#include "hand.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GAME CLASS

class Game{ // initialises a new game of Poker

public:

  Game();
  ~Game();
  // void debug(); // a debugger program I make to check whether the scores are rightuflly allocated
  void start(); // starts the game after initialising
  void show_players(); // made for testing purporses
  void deal_pocket(Deck &deck); // deal pocket cards to each player
  void deal_flop(Deck &deck); // deals first 3 community cards
  void deal_turn(Deck &deck); // deals 4th community card
  void deal_river(Deck &deck); // deals 5th community card
  //N.B essentially deal_turn and deal_river have some methods, but I made different functions as to avoid any unforseen subtle errors, can change later
  void show_board();
  // std::vector<Card> get_board();
  void declare_winner(); // determines the winner from the scores given to the Player objects
  void next_round(); // clears the pocket and community cards, starts a new game

protected:
  int _number_of_players;
  int _community_pot = 0; // this is the money that will be on the table frmo Player objects that have folded
  int _big_blind = 100;
  int _small_blind = 0.5*_big_blind;
  std::vector<Player> _players; // a vector container to contain all Player object profiles
  std::vector<Player>::iterator _players_iter;
  std::vector<Card> _board; // this is where the community Card objects are placed
  std::vector<Card>::iterator _board_iter; // for checking if _board has at least 3 cards after flop


};


#endif
