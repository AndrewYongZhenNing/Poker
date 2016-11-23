#include "hand.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// HAND CLASS

Hand::Hand(Player &player, std::vector<Card> board){ // evaluates the hands of each player at showdown

  player.show_name();

  _temp_player = player.get_pocket(); // now temp holds the specific player's pocket cards
  std::cout << "Size of _temp_player is: " << _temp_player.size() << std::endl; // interesting, this returns the size 0, hence segmentation fault - there's nothing in this!

  // std::cout << "First card: " << temp.getSuit() << temp.getValue() << std::endl;
  for (_temp_iter = _temp_player.begin();_temp_iter != _temp_player.end(); _temp_iter++){ //fill _hand container with player's pocket cards

    Card temp = *_temp_iter;

    std::cout <<"has the following cards:\n" << temp.getSuit() << temp.getValue() << std::endl;

    _hand.push_back(*_temp_iter); //dereferencing _temp_iter will give one of the two cards in the Player's pockets where the pointer is pointing at

  }

  for (_temp_iter = board.begin();_temp_iter != board.end(); _temp_iter++){ //fill _hand container with player'board's community cards

    _hand.push_back(*_temp_iter); // dereferencing _temp_iter will give one of the community cards in the board at game

  }

  std::cout << "\nThe hand is: " << std::endl;

  for (_temp_iter = _hand.begin();_temp_iter != _hand.end(); _temp_iter++){ // testing purposes

    Card temp = *_temp_iter;

    std::cout << temp.getSuit() << temp.getValue() << " " << std::flush;

  }

  std::cout << "" << std::endl;

}

Hand::~Hand(){};
