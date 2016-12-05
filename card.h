#ifndef _CARD_KLASS_
#define _CARD_KLASS_

//Relevant libraries
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

class Card{

public:

  Card(char Suit, int value); // initialises the constructor
  // Card();
  ~Card();

  char getSuit(); // get the suit of the Card object
  int getValue(); // get the value of the Card object
  void show_card(); // displays the Card object on the terminal (with A K Q J in place of 1,13,12,11)
  // N.B void is for display purposes; for sorting and rearrangements must use getSuit() and getValue()
  bool operator<(const Card &rhs); // used to sort Card objects by values later
  void switch_ace(); // in the presence of a face value 2, A can switch from being a high valued Card object to a low-valued Card object


protected:

  char _suit;
  int _value;


};

#endif
