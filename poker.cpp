#include "poker.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GAME CLASS

Game::Game(){ // upon initialising, set number of players (Player objects), create a Deck (object) and deal cards to Player objects

  std::cout << "Welcome to a game of Poker." << std::endl;


  std::cout << "Please enter the number of players:";
  std::cin >> _number_of_players;

  // HOW DO I GET IT TO EXIT LOOP?
  // try{
  //   if (_number_of_players < 3){
  //     throw 1;
  //   }
  // }
  //
  // catch(int exception){
  //   std::cerr << "Insufficient players. Please ensure at least 3 players participate in the game." << std::endl;
  //
  // }

  for(int i = 1; i <= _number_of_players; i++){ // create new players

    std::cout << "Player " << i << ":" << std::endl;
    Player p = Player();
    _players.push_back(p);

  }

  std::random_shuffle(_players.begin(),_players.end());// shuffles the order of the Player objects such that game does not always start with Player 1 as the dealer

  std::cout << "\nBegin game.\n" << std::endl;

  start(); //starts the actual dynamic of the game


}

Game::~Game(){};

// void Game::debug(){
//
//   int rank = 0;
//
//   std::cout << "Select rank to evaluate: ";
//   std::cin >> rank;
//
//   while(start() != rank){
//     start();
//   }
// }

void Game::start(){

  Deck game_deck = Deck(); //initialises a Deck (object) of cards for gameplay
  std::cout << "Shuffling deck...\n" << std::endl;
  game_deck.shuffle();

  std::cout << "Dealer: " << _players.back().show_name() << " \nSmall Blind: " << _players[0].show_name() << " \nBig Blind: " << _players[1].show_name() << std::endl;
  std::cout << "\nDealing pocket cards to players...\n" << std::endl;

  deal_pocket(game_deck); // starts dealing each player their pocket cards

  //BETTING HAPPENS HERE
  std::cout << "\nBetting begins: " << std::endl;
  _players[1].bet(_small_blind);
  _players[2].bet(_big_blind);

  for (int i =2; i < _players.size(); i++){
    char response;
    std::cout << _players[i].show_name() << ": Would you like to call/check(c), raise(r), or fold(f)?\nEnter your command (c,r or f)";
    std::cin >> response;

    if(response == 'c'){// call: match with the current raised value
      //do something
    }

    else if(response == 'r'){
      //do something else
    }

    else if(response == 'f'){
      //do something else
    }

    else{
      std::cerr << "Invalid response. Please try again." << std::endl;
    }
  }

  // std::cout << "Total pot: " << _pot << std::endl;

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
    Hand(_players[i],_board); // takes in Player object's pocket cards and the community cards to go through evaluation

  }

  declare_winner(); // declares the winner and ends the game

  // next_round(); //container gets destructed when it goes out of scope

}

void Game::show_players(){ // test purposes: show how many players are in the game

  for (_players_iter = _players.begin(); _players_iter != _players.end(); _players_iter++){

    Player temp = *_players_iter;
    temp.show_name();

  }

}

void Game::deal_pocket(Deck &deck){ // deal pocket cards to each player

  for(int i=0;i<_players.size(); i++){ // iterating through every player
    for (int j = 0; j < 2; j++){ // deals two cards

      Card temp_card = deck.get_top(); // gets the top card from game_deck Deck
      _players[i].deal(temp_card); // pushes top card of game deck into player's method of dealing pocket cards
      deck.new_top(); // ensures that the top card is removed

    }
  }

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
    Card community_card = *_board_iter;

    community_card.show_card(); // displays the Card object

  }

}


// not sure if get_board() is useful, commented out for now
// std::vector<Card> Game::get_board(){ // returns the vector container that has the community cards in it
//
//   return _board;
//
// }

void Game::declare_winner(){

  int j = 0;
  bool draw = false;
  Player winner = _players[j]; // assume the first Player object in the _player container is the winner

  for (int i =j+1; i < _players.size(); i++){
    if(winner.get_score() <= _players[i].get_score()){
      if (winner.get_score() == _players[i].get_score()){ // potentially a draw
        draw = true;

      }

      else{ // the candidate winner has the lower score, transfer the information of the candidate winner to the winner object
        winner = _players[i]; // let the winner be the i'th Player object which has the presently highest score
        draw = false; // put this line here just in case previous there were cases where other Plyers objects have the same score
      }

    }

  }

  if (!draw){
    std::cout << "Congratulations!\nThe winner is: " << winner.show_name() << std::endl;
    //winner.collect_pot(_pot); // increases the winner's bankroll by the amount of bet on the particular round

  }

  else if (draw){
    std::cout << "It's a draw between:" << std::endl;

    for(int p = 0; p < _players.size(); p++){
      if(_players[p].get_score() == winner.get_score()){ // prints those who share the same score
        std::cout << _players[p].show_name() << std::endl;
      }
    }
  }

}

void Game::next_round(){
  _board.clear(); // destroys all community Card objects

  for (int i = 0; i < _players.size(); i++){ // removes all pocket Card objects from all Player objects
    _players[i].empty_pocket();
  }

  start();

}
