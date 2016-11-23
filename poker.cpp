#include "poker.h"


// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //CARD CLASS
//
// Card::Card(char Suit, int value){
//
//   _suit = Suit;
//   _value = value;
//
// }
//
// // Card::Card(): _suit('a'),_value(0){}; // initialises
//
// Card::~Card(){};
//
// char Card::getSuit(){
//
//   // std::cout << "The suit is: " << _suit << std::endl;
//   // std::cout << _suit << std::endl;
//
//   return _suit;
//
// }
//
// int Card::getValue(){
//
//   // std::cout << "The value is: " << _value << std::endl;
//   // std::cout << _value << std::endl;
//
//   return _value;
// }
//
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // DECK CLASS
//
// Deck::Deck(){
//
//   for (int i = 0; i < 4; i++){ // for every suit...
//
//     for (int j = 1; j < 14; j++){ //... give it twelve cardsd (Card object)
//
//       Card card(_suit[i],j);
//
//       /* THIS IS JUST FOR CHECKING THAT THE DECK HAS ALL THE VALUES FOR EVERY SUIT
//
//       // card.getSuit();
//       // card.getValue();
//
//       // std::cout << card.getSuit() << card.getValue() << std::endl;
//       // std::cout << card.getSuit() << std::endl;
//
//       */
//
//       _deck.push_back(card);
//
//     }
//   }
//
//
// }
//
// Deck::~Deck(){};
//
// void Deck::shuffle(){ // randomly shuffles the deck using srand in main
//   std::random_shuffle(_deck.begin(),_deck.end());
// }
//
// void Deck::show(){ // display the entire deck on the terminal
//
//   for (_deck_iter = _deck.begin(); _deck_iter != _deck.end(); _deck_iter++){
//     Card temp = *_deck_iter; // dereferences a value into a temporary Card object
//     std::cout << temp.getSuit() << temp.getValue() << std::endl;
//   }
//
// }
//
// void Deck::new_top(){ // takes the current top card and pushes it back to the bottom of the deck [a tradition, apparently]
//
//   _deck_iter = _deck.begin(); // points the pointer at the top most element
//
//   _deck.push_back(*_deck_iter); //pushes a value equivalent the Card object iter is pointing at (the top card) to the bottom of the deck
//   _deck.erase(_deck_iter); // now erase top Card object to avoid duplication
//   _deck.pop_back();
//
// }
//
// Card Deck::get_top(){ // gets the card at the top of the Deck (container)
//
//   _deck_iter = _deck.begin();
//   Card top_card = *_deck_iter;
//
//   return top_card;
//
//   // _deck.erase(_deck_iter); // ensures that top card is gone from the deck
//
//   // std::cout << top_card.getSuit() << top_card.getValue() << std::endl; // for visiual purposes on the temrinal
//
// }
//
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // PLAYER CLASS
//
// Player::Player(){ //upon initialising, give player a name and container to hold two cards (hole/pocket cards)
//
//   std::cout << "\nPlease enter your name below:\n";
//   std::cin >> player_name;
//   std::cout << player_name << " has joined the game.\n" << std::endl;
//
// }
//
// Player::~Player(){};
//
// void Player::show_name(){
//   std::cout << player_name << std::endl;
// }
//
// // void Player::show_pocket(){ // reveals the pocket card of the Player
// //
// //   std::cout << player_name << ", here are your pocket cards: " << std::endl;
// //
// //   for (_pocket_iter = _pocket_cards.begin(); _pocket_iter != _pocket_cards.end(); _pocket_iter++){
// //     std:: cout << *_pocket_iter << " " << std::flush;
// //   }
// //
// //   std::cout << "" << std::endl;
// //
// //
// // }
// //
// // void Player::deal(){ //dereferences the Deck iter into the _pocket_cards container
// //
// //
// //
// // }
//
// void Player::deal(Card &top_card){ // takes in a Deck object, then use get_top() method to get the top Card object, then push_back into Player's pocket container
//
//   // Card temp = deck.get_top(); // method get_top() returns a Card object, which fits the LHS temp
//   _pocket_cards.push_back(top_card); // push_back the top card into pocket_cards container
//   // deck.erase()
//
// }
//
// std::vector<Card> Player::get_pocket(){ // returns the vector container with pocket cards in it
//   std::cout << "In get_pocket(), size of _pocket_cards is:" << _pocket_cards.size() << std::endl;
//   return _pocket_cards; // << this is a vector
// }
//
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // HAND CLASS
//
// Hand::Hand(Player &player, std::vector<Card> board){ // evaluates the hands of each player at showdown
//
//   player.show_name();
//
//   _temp_player = player.get_pocket(); // now temp holds the specific player's pocket cards
//   std::cout << "Size of _temp_player is: " << _temp_player.size() << std::endl; // interesting, this returns the size 0, hence segmentation fault - there's nothing in this!
//
//   // std::cout << "First card: " << temp.getSuit() << temp.getValue() << std::endl;
//   for (_temp_iter = _temp_player.begin();_temp_iter != _temp_player.end(); _temp_iter++){ //fill _hand container with player's pocket cards
//
//     Card temp = *_temp_iter;
//
//     std::cout <<"has the following cards:\n" << temp.getSuit() << temp.getValue() << std::endl;
//
//     _hand.push_back(*_temp_iter); //dereferencing _temp_iter will give one of the two cards in the Player's pockets where the pointer is pointing at
//
//   }
//
//   for (_temp_iter = board.begin();_temp_iter != board.end(); _temp_iter++){ //fill _hand container with player'board's community cards
//
//     _hand.push_back(*_temp_iter); // dereferencing _temp_iter will give one of the community cards in the board at game
//
//   }
//
//   std::cout << "\nThe hand is: " << std::endl;
//
//   for (_temp_iter = _hand.begin();_temp_iter != _hand.end(); _temp_iter++){ // testing purposes
//
//     Card temp = *_temp_iter;
//
//     std::cout << temp.getSuit() << temp.getValue() << " " << std::flush;
//
//   }
//
//   std::cout << "" << std::endl;
//
// }
//
// Hand::~Hand(){};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GAME CLASS

Game::Game(){ // upon initialising, set number of players (Player objects), create a Deck (object) and deal cards to Player objects

  std::cout << "Welcome to a game of Poker." << std::endl;

  Deck game_deck = Deck(); //initialises a Deck (object) of cards for gameplay
  game_deck.shuffle();

  // std::cout << "[TEST] This is the game deck" << std::endl; // test purposes
  //
  // game_deck.show(); // test purposes

  std::cout << "Please enter the number of players:";
  std::cin >> _number_of_players;

  for(int i = 1; i <= _number_of_players; i++){ // create new players

    std::cout << "Player " << i << ":" << std::endl;
    Player p = Player();
    _players.push_back(p);

  }

  deal_pocket(game_deck); // starts dealing each player their pocket cards

  //BETTING HAPPENS HERE, BUT FIRST ASSUME NO BETTING AND GO STRAIGHT TO FLOP

  deal_flop(game_deck);

  std::cout << "Community cards at flop: " << std::endl;

  show_board();

  deal_turn(game_deck);

  std::cout << "\nCommunity cards at turn: " << std::endl;

  show_board();

  deal_river(game_deck);

  std::cout << "\nCommunity cards at river: " << std::endl;

  show_board();

  std::cout << "" << std::endl;

  // all the community cards are now on the table, now determine rank

  for (int i = 0; i < _number_of_players; i++){
    Hand(_players[i],_board);
  }


}

Game::~Game(){};

void Game::show_players(){ // test purposes: show how many players are in the game

  for (_players_iter = _players.begin(); _players_iter != _players.end(); _players_iter++){

    Player temp = *_players_iter;
    temp.show_name();

  }

}

void Game::deal_pocket(Deck &deck){ // deal pocket cards to each player

//  for (_players_iter = _players.begin(); _players_iter != _players.end(); _players_iter++){

    //int i = 0;
    //Player temp_player = *_players_iter; // dereferences the pointer, now temp holds the Player object iter is pointing at in the vector
    for(int i=0;i<_players.size(); i++){ // iterating through every player
      for (int j = 0; j < 2; j++){ // deals two cards

        Card temp_card = deck.get_top(); // gets the top card from game_deck Deck
        _players[i].deal(temp_card); // pushes top card of game deck into player's method of dealing pocket cards
        deck.new_top(); // ensures that the top card is removed

      }
    }

  //}

}

void Game::deal_flop(Deck &deck){ // deals first 3 community cards

  for (int i = 0; i < 3; i++){

    Card community_card = deck.get_top();
    _board.push_back(community_card); // adds 3 cards onto board vector
    deck.new_top();

  }

}

void Game::deal_turn(Deck &deck){ // deals the 4th community card

  Card community_card = deck.get_top();
  _board.push_back(community_card); // adds one card onto board vector during turn
  deck.new_top();

}

void Game::deal_river(Deck &deck){ // deals the 5th community card

  Card community_card = deck.get_top();
  _board.push_back(community_card); // adds one final Card object onto board vector during river
  deck.new_top();

}

void Game::show_board(){ // display the board - essential for the game

  for (_board_iter = _board.begin(); _board_iter!=_board.end(); _board_iter++){ // for printing out community card
    Card temp = *_board_iter;

    if (temp.getValue() == 1){

      std::cout << temp.getSuit() << "A" << " " << std::flush; // flush shouldn't be affected here

    }

    else if (temp.getValue() == 11){
      std::cout << temp.getSuit() << "J" << " " << std::flush; // flush shouldn't be affected here
    }

    else if (temp.getValue() == 12){

      std::cout << temp.getSuit() << "Q" << " " << std::flush;

    }

    else if (temp.getValue() == 13){

      std::cout << temp.getSuit() << "K" << " " << std::flush;

    }

    else{
      std::cout << temp.getSuit() << temp.getValue()  << " " << std::flush; // original statement
    }

  }

}

std::vector<Card> Game::get_board(){ // returns the vector container that has the community cards in it

  return _board;

}
