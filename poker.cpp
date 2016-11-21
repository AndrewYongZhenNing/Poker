#include "poker.h"

Card::Card(char Suit, int value){

  _suit = Suit;
  _value = value;

}

Card::Card(): _suit('a'),_value(0){};

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

Deck::Deck(){

  char _suit[4] = {'H', 'C', 'S', 'D'}; // defines the synbols for each suit using char

  for (int i = 0; i < 4; i++){ // for every suit...

    for (int j = 1; j < 14; j++){ //... give it twelve cardsd (Card object)

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
    Card temp = *_deck_iter;
    std::cout << temp.getSuit() << temp.getValue() << std::endl;
  }

  // std::cout << "does nothing" << std::endl;

}

void Deck::new_top(){ // takes the current top card and pushes it back to the bottom of the deck [a tradition, apparently]
  _deck_iter = _deck.begin(); // points the pointer at the top most element

  _deck.push_back(*_deck_iter); //pushes a value equivalent the Card object iter is pointing at (the top card) to the bottom of the deck
  _deck.erase(_deck_iter); // now erase top Card object to avoid duplication

}

Player::Player(){ //upon initialising, give player a name and container to hold two cards (hole/pocket cards)

  std::cout << "\nEnter your name below:";
  std::cin >> player_name;
  std::cout << player_name << " has joined the game." << std::endl;

}

Player::~Player(){};
