#ifndef _DECK_KLASS_
#define _DECK_KLASS_

//Relevant libraries
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

//Relevant class header files
#include "card.h" // such that I can use return types of Card class

class Deck{

public:

  Deck();
  ~Deck();

  void shuffle(); // randomises the sequence of cards
  void show(); // test purposes: show the entire deck
  void new_top(); // replaces the top card (can also be used analogously as pop_front()!)
  Card get_top(); // returns an object of type Card
  void remove_card(Card &c); // remove a selected Card object from the Deck (for simulation purposes)

protected:

  char _suit[4]; // defines the symbols for each suit using char
  std::vector<Card> _deck; // takes in objects constructed by Card
  std::vector<Card>::iterator _deck_iter; // a pointer for going through the Deck

};


#endif
