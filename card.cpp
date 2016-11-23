#include "card.h"

Card::Card(char Suit, int value){

  _suit = Suit;
  _value = value;

}

// Card::Card(): _suit('a'),_value(0){}; // initialises

Card::~Card(){};

char Card::getSuit(){

  // std::cout << "The suit is: " << _suit << std::endl;
  // std::cout << _suit << std::endl;

  return _suit;

}

int Card::getValue(){

  // std::cout << "The value is: " << _value << std::endl;
  // std::cout << _value << std::endl;

  return _value;
}
