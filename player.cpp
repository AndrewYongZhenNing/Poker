#include "player.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PLAYER CLASS

Player::Player(){ //upon initialising, give player a name and container to hold two cards (hole/pocket cards)

  std::cout << "\nPlease enter your name below:\n";
  std::cin >> player_name;
  std::cout << player_name << " has joined the game.\n" << std::endl;

}

Player::~Player(){};

std::string Player::show_name(){
  // std::cout << player_name << std::endl;
  return player_name;
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

  return _pocket_cards; // << this is a vector
}

void Player::assign_score(int hand_score){

  _score = hand_score;

}

int Player::get_score(){

  return _score;
}

void Player::show_score(){

  std::cout << player_name << "'s score is: " << _score << "\n" << std::endl;

}

void Player::empty_pocket(){ // empties the pocket container of pocket Card objects

  _pocket_cards.clear();

}

void Player::bet(int amount){

  _bankroll -= amount; // deducts the amount from Player object's bankroll
  _pot += amount; // puts the amount into Player object's pot
}

void Player::call(int remain){
  if (_bankroll > 0){
    int amount = remain - _pot;
    bet(amount);
  }

}

void Player::raise_(int amount){
  if(_bankroll >0){
    call(amount);
  }
}

// void Player::raise(){
//   call()
// }

int Player::get_pot(){
  return _pot;
}

void Player::show_bankroll(){
  std::cout << "Bankroll: " << _bankroll << std::endl;
}

// void Player::collect_pot(int pot_money){
//   _bankroll += pot_money;
// }
