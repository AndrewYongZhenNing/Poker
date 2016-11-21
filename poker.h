#ifndef _POKER_KLASS_
#define _POKER_KLASS_

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CARD CLASS

class Card{

public:

  Card(char Suit, int value); // initialises the constructor
  // Card();
  ~Card();

  char getSuit(); // get the suit of the Card object
  int getValue(); // get the value of the Card object


protected:

  char _suit;
  int _value;


};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DECK CLASS

class Deck{

public:

  Deck();
  ~Deck();

  void shuffle(); // randomises the sequence of cards
  void show(); // test purposes: show the entire deck
  void new_top(); // replaces the top card (can also be used analogously as pop_front()!)
  Card get_top(); // returns an object of type Card

protected:

  char _suit[4] = {'H', 'C', 'S', 'D'}; // defines the symbols for each suit using char
  std::vector<Card> _deck; // takes in objects constructed by Card
  std::vector<Card>::iterator _deck_iter; // a pointer for going through the Deck

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PLAYER CLASS

class Player{ // creates new Player (objects)

public:
  Player();
  ~Player();
  void show_name();
  // void show_pocket(); // reveals the pocket card of the Player
  void deal(Card &top_card); //dereferences the Deck iter into the _pocket_cards container

protected:
  std::string player_name;
  std::vector<Card> _pocket_cards; // container with two spaces to hold the cards
  std::vector<Card>::iterator _pocket_iter; // maybe redundant

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GAME CLASS

class Game{ // initialises a new game of Poker

public:

  Game();
  ~Game();
  void show_players(); // made for testing purporses
  void deal_pocket(Deck &deck); // deal pocket cards to each player
  void deal_flop(Deck &deck); // deals first 3 community cards
  void deal_turn(Deck &deck); // deals 4th community card
  void deal_river(Deck &deck); // deals 5th community card
  //N.B essentially deal_turn and deal_river have some methods, but I made different functions as to avoid any unforseen subtle errors, can change later
  void show_board();

protected:
  int _number_of_players;
  std::vector<Player> _players; // a vector container to contain all Player object profiles
  std::vector<Player>::iterator _players_iter;
  std::vector<Card> _board; // this is where the community Card objects are placed
  std::vector<Card>::iterator _board_iter; // for checking if _board has at least 3 cards after flop

};


#endif
