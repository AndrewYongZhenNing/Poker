#include "deck.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DECK CLASS

Deck::Deck(){

   _suit[0] = 'H' ;
   _suit[1] = 'C';
   _suit[2] = 'S';
   _suit[3] = 'D';

  for (int i = 0; i < 4; i++){ // for every suit...

    for (int j = 2; j < 15; j++){ //... give it twelve cards (Card object)

      Card card(_suit[i],j);

      /* THIS IS JUST FOR CHECKING THAT THE DECK HAS ALL THE VALUES FOR EVERY SUIT

      // card.getSuit();
      // card.getValue();

      // std::cout << card.getSuit() << card.getValue() << std::endl;
      // std::cout << card.getSuit() << std::endl;

      */

      _deck.push_back(card);

    }
  }


}

Deck::~Deck(){};

void Deck::shuffle(){ // randomly shuffles the deck using srand in main
  std::random_shuffle(_deck.begin(),_deck.end());
}

void Deck::show(){ // display the entire deck on the terminal

  for (_deck_iter = _deck.begin(); _deck_iter != _deck.end(); _deck_iter++){
    Card temp = *_deck_iter; // dereferences a value into a temporary Card object
    std::cout << temp.getSuit() << temp.getValue() << std::endl;
  }

}

void Deck::new_top(){ // takes the current top card and pushes it back to the bottom of the deck [a tradition, apparently]

  _deck_iter = _deck.begin(); // points the pointer at the top most element

  _deck.push_back(*_deck_iter); //pushes a value equivalent the Card object iter is pointing at (the top card) to the bottom of the deck
  _deck.erase(_deck_iter); // now erase top Card object to avoid duplication
  _deck.pop_back();

}

Card Deck::get_top(){ // gets the card at the top of the Deck (container)

  _deck_iter = _deck.begin();
  Card top_card = *_deck_iter;

  return top_card;

  // _deck.erase(_deck_iter); // ensures that top card is gone from the deck

  // std::cout << top_card.getSuit() << top_card.getValue() << std::endl; // for visiual purposes on the temrinal

}

void Deck::remove_card(Card &c){ // remove a selected Card object from the Deck (for simulation purposes)

  for(int i = 0; i < _deck.size(); i++){
    if (_deck[i].getSuit() == c.getSuit() && _deck[i].getValue() == c.getValue()){
      _deck.erase(_deck.begin()+i);
    }
  }

}
