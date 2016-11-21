#include "poker.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//CARD CLASS

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DECK CLASS

Deck::Deck(){

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GAME CLASS

Game::Game(){ // upon initialising, set number of players (Player objects), create a Deck (object) and deal cards to Player objects

  std::cout << "Welcome to a game of Poker." << std::endl;

  Deck game_deck = Deck(); //initialises a Deck (object) of cards for gameplay
  game_deck.shuffle();

  std::cout << "[TEST] This is the game deck" << std::endl; // test purposes

  game_deck.show(); // test purposes

  std::cout << "Please enter the number of players:";
  std::cin >> _number_of_players;

  for(int i = 1; i <= _number_of_players; i++){ // create new players

    std::cout << "Player " << i << ":" << std::endl;
    Player p = Player();
    _players.push_back(p);

  }

  deal_pocket(game_deck); // starts dealing each player their pocket cards

  std::cout << "[TEST] After dealing two card per player" << std::endl;
  game_deck.show();

}

Game::~Game(){};

void Game::show_players(){ // test purposes: show how many players are in the game

  for (_players_iter = _players.begin(); _players_iter != _players.end(); _players_iter++){

    Player temp = *_players_iter;
    temp.show_name();

  }

}

void Game::deal_pocket(Deck &deck){ // deal pocket cards to each player

  for (_players_iter = _players.begin(); _players_iter != _players.end(); _players_iter++){
    int i = 0;
    Player temp = *_players_iter; // dereferences the pointer, now temp holds the Player object iter is pointing at in the vector

    for (int i = 0; i < 2; i++){ // deals two cards

      Card temp_card = deck.get_top(); // gets the top card from game_deck Deck
      temp.deal(temp_card); // pushes top card of game deck into temp's (which is a player's) method
      deck.new_top(); // ensures that the top card is removed

    }


    // something like pocket_cards.push_back(game_deck.get_top())


  }

}
