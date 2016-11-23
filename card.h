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


protected:

  char _suit;
  int _value;


};

#endif
