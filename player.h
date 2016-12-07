#ifndef _PLAYER_KLASS_
#define _PLAYER_KLASS_

//Relevant libraries
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>

//Relevant class header files
#include "card.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PLAYER CLASS

class Player{ // creates new Player (objects)

public:
  Player();
  Player(std::string AI_name);
  ~Player();
  std::string show_name();
  void show_pocket(); // reveals the pocket card of the Player
  void deal(Card &top_card); //dereferences the Deck iter into the _pocket_cards container
  std::vector<Card> get_pocket(); // gets a vector container full of Card objects
  void get_hand(std::vector<Card> hand); // pass the vector container with the fully evaluated hand from Hand class
  std::vector<Card> get_hand(); // overload get_hand method to just return the evaluated hand of each player
  void assign_score(int hand_score);
  int get_score(); // returns the score from the Player object's hand
  void show_score(); //test method to check the scores during development
  void empty_pocket(); // empties the pocket container of pocket Card objects
  void bet(int amount); // returns the amount the Player object's puts into the pot, in the meantime deducting that amount from Player object's bankroll
  void call(int remain); // bets the amount such that the Player object's pot is level with the highest amount of the round
  void raise_(int amount); // raises the call amount by one unit (1 _big_blind at pre-flop and flop, 2 _big_blind at turn and river)
  void show_bankroll();// displays bankroll during game
  int get_bankroll();
  int get_pot();
  void clear_pot();
  void claim_pot(int& community_pot); // winner Player object claims the community pot and appends the amount into bankroll
  // void collect_pot(int pot_money); // collects the pot [FOR WINNERS ONLY]
  bool are_you_AI(); // used a every decision-making point in the game to discern AI from human Player objects

protected:
  std::string player_name;
  std::vector<Card> _pocket_cards; // container with two spaces to hold the cards
  std::vector<Card>::iterator _pocket_iter; // maybe redundant
  std::vector<Card> _player_hand;
  int _score = 0;
  int _bankroll = 1000; // every Player object gets a bankroll of default 1000 C++ currency on initialisation
  int _pot = 0;
  bool _AI = false;

};

class AI: public Player{
//at the moment AI has everything Player has, so looks a bit redundant; but when AI gets more complex I will add evaluation methods strictly for AI in helping them determine to bet or not

public:
  AI(std::string name);
  ~AI();

};

#endif
