#include "card.h"

Card::Card(char Suit, int value){

  _suit = Suit;
  _value = value;

}

// Card::Card(): _suit('a'),_value(0){}; // initialises

Card::~Card(){};

char Card::getSuit(){

  return _suit;

}

int Card::getValue(){


  return _value;
}

void Card::show_card(){ // displays the Card object on the terminal (with A K Q J in place of 1,13,12,11)

  if (_value == 14 || _value == 1){

    std::cout << _suit << "A" << " " << std::flush; // flush shouldn't be affected here

  }

  else if (_value == 11){
    std::cout << _suit << "J" << " " << std::flush; // flush shouldn't be affected here
  }

  else if (_value == 12){

    std::cout << _suit << "Q" << " " << std::flush;

  }

  else if (_value == 13){

    std::cout << _suit << "K" << " " << std::flush;

  }

  else{
    std::cout << _suit << _value  << " " << std::flush; // original statement
  }

}

bool Card::operator<(const Card &rhs){ // returns a boolean that the right hand side Card object's value is larger than the left hand side Card object's value
  return (_value < rhs._value);
}

void Card::switch_ace(){
  _value = 1;
}
