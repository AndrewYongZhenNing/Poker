#ifndef _POKER_KLASS_
#define _POKER_KLASS_

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

class Card{

public:

  Card(char Suit, int value); // initialises the constructor
  Card();
  ~Card();

  char getSuit();
  int getValue();


protected:

  char _suit;
  int _value;


};

class Deck{ // try inherit? not necessary?

public:

  Deck();
  ~Deck();

  void shuffle();
  void show();
  void new_top();

protected:

  // char _suit[4];
  std::vector<Card> _deck; // takes in objects constructed by Card
  std::vector<Card>::iterator _deck_iter; // a pointer for going through the Deck

};

class Player{ // creates new Player (objects)

public:
  Player();
  ~Player();

protected:
  std::string player_name;
  std::vector<Card> _pocket_cards; // container with two spaces to hold the cards
  std::vector<Card>::iterator _pocket_iter;

};


#endif
