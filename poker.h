#ifndef _POKER_KLASS_
#define _POKER_KLASS_

//Relevant libraries
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>

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
  void bet(int &amount, int raise_unit); // returns the call amount; //pass call amount by reference as it is needed to go through the entire game round
  void deal_pocket(Deck &deck); // deal pocket cards to each player
  void deal_flop(Deck &deck); // deals first 3 community cards
  void deal_turn(Deck &deck); // deals 4th community card
  void deal_river(Deck &deck); // deals 5th community card
  //N.B essentially deal_turn and deal_river have some methods, but I made different functions as to avoid any unforseen subtle errors, can change later
  void show_board();
  // std::vector<Card> get_board();
  void declare_winner(); // determines the winner from the scores given to the Player objects

  void simulation();
  float simulation_start(Card c1, Card c2, char command, int limit); // to be used for statistical analysis, but also by AI to determine odds of winning
  void s_declare_winner(int &win, char command); // determines the winning percentage in a simulation

protected:
  int _number_of_players;
  int _community_pot = 0; // this is the money that will be on the table from Player objects that have folded
  int _big_blind = 100;
  int _small_blind = 0.5*_big_blind;
  int _call_counter = 0; // determines whether to start next round of betting or not
  std::vector<Player> _players; // a vector container to contain all Player object profiles
  std::vector<Player>::iterator _players_iter;
  std::vector<Player> _active_players;
  std::vector<Card> _board; // this is where the community Card objects are placed
  std::vector<Card>::iterator _board_iter; // for checking if _board has at least 3 cards after flop
  // For AI
  bool _include_AI = false;
  // For Statistical Analysis
  char _response; // for playing game/statistical analysis, including/excluding AI etc etc
  char _face;
  std::string _value;
  int _limit = 0; // variable to hold the number of simulations to perform
  bool question = false; // generalised boolean used with while loops at points where user input is necessary such that wrong inputs do not cause problems
  int _total = 0;
  int _win = 0;


};


#endif
