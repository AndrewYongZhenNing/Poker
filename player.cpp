#include "player.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PLAYER CLASS

Player::Player(){ //upon initialising, give player a name and container to hold two cards (hole/pocket cards)

  std::cout << "\nPlease enter your name below:\n";
  std::cin >> player_name;
  std::cout << player_name << " has joined the game.\n" << std::endl;

}

Player::~Player(){};

void Player::show_name(){
  std::cout << player_name << std::endl;
}

// void Player::show_pocket(){ // reveals the pocket card of the Player
//
//   std::cout << player_name << ", here are your pocket cards: " << std::endl;
//
//   for (_pocket_iter = _pocket_cards.begin(); _pocket_iter != _pocket_cards.end(); _pocket_iter++){
//     std:: cout << *_pocket_iter << " " << std::flush;
//   }
//
//   std::cout << "" << std::endl;
//
//
// }
//
// void Player::deal(){ //dereferences the Deck iter into the _pocket_cards container
//
//
//
// }

void Player::deal(Card &top_card){ // takes in a Deck object, then use get_top() method to get the top Card object, then push_back into Player's pocket container

  // Card temp = deck.get_top(); // method get_top() returns a Card object, which fits the LHS temp
  _pocket_cards.push_back(top_card); // push_back the top card into pocket_cards container
  // deck.erase()

}

std::vector<Card> Player::get_pocket(){ // returns the vector container with pocket cards in it
  std::cout << "In get_pocket(), size of _pocket_cards is:" << _pocket_cards.size() << std::endl;
  return _pocket_cards; // << this is a vector
}
