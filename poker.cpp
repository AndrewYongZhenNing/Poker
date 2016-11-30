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

  // Add Player objects on to a container of active Player objects now
  for (int i = 0;i < _players.size(); i++){
    _active_players.push_back(_players[i]);
  }


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

  // last three Player objects of the game are Dealer, Small and Big Blind respectively
  std::cout << "Dealer: " << _active_players.rbegin()[2].show_name() << " \nSmall Blind: " << _active_players.rbegin()[1].show_name() << " \nBig Blind: " << _active_players.rbegin()[0].show_name() << std::endl;
  std::cout << "\nDealing pocket cards to players...\n" << std::endl;

  deal_pocket(game_deck); // starts dealing each player their pocket cards

  //BETTING HAPPENS HERE
  std::cout << "\nBetting begins: " << std::endl;

  int call_amount = 0; // a reference amount of raise in each round

  _active_players.rbegin()[1].bet(_small_blind);
  _active_players.rbegin()[0].bet(_big_blind);

  call_amount += _big_blind;

  bet(call_amount,_big_blind); // pre-flop betting happens in a for loop in here

  // bet_next_round(call_amount,_big_blind); // in order to move to next round, all Player objects must have same amount in their pot

  std::cout << "Players remaining: " << std::endl;

  for (_players_iter = _active_players.begin(); _players_iter != _active_players.end(); _players_iter++){
    Player temp = *_players_iter;
    std::cout << temp.show_name() << std::endl;
  }

  deal_flop(game_deck);

  std::cout << "Community cards at flop: " << std::endl;

  show_board();

  std::cout << "" << std::endl;

  bet(call_amount,_big_blind); // flop betting happens in a for loop in here

  // bet_next_round(call_amount,_big_blind);

  deal_turn(game_deck);

  std::cout << "\nCommunity cards at turn: " << std::endl;

  show_board();

  bet(call_amount,2*_big_blind); // post betting happens in a for loop in here

  // bet_next_round(call_amount, 2*_big_blind);

  deal_river(game_deck);

  std::cout << "\nCommunity cards at river: " << std::endl;

  show_board();

  std::cout << "" << std::endl;

  bet(call_amount,2*_big_blind); // post betting happens in a for loop in here

  // bet_next_round(call_amount, 2*_big_blind);

  // all the community cards are now on the table, now determine rank

  for (int i = 0; i < _active_players.size(); i++){
    Hand(_active_players[i],_board); // takes in Player object's pocket cards and the community cards to go through evaluation

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

void Game::bet(int &amount, int raise_unit){

  char response = 'n';

  for (int i = 0; i < _active_players.size(); i++){

    std::cout << _active_players[i].show_name() << ": Would you like to call/check(c), raise(r), or fold(f)?\nEnter your command (c,r or f)";
    std::cin >> response;

    //call
    if(response == 'c'){// call: match with the current raised value
      _active_players[i].call(amount);
      _active_players[i].show_bankroll();
      _call_counter ++;
    }

    // raise
    else if(response == 'r'){

      amount+= raise_unit; // raise by one unit of big blind
      _active_players[i].raise_(amount);
      // _active_players[i].call(amount); // first even with the current highest
      // _active_players[i].bet(raise_unit); // then add one unit of big blind
      _active_players[i].show_bankroll();
      // amount+= raise_unit; // raise by one unit of big blind
      _call_counter = 0;
    }

    // fold
    else if(response == 'f'){
      // char fold_response;
      // std::cout << "You selected fold(f), are you sure?"
      std::cout << "Player " << _active_players[i].show_name() << " has folded." << std::endl;
      _active_players.erase(_active_players.begin()+i); //removes current Player object from the container of active Player objects; will rejoin in the subsequent games
      i --; // this is to ensure that the pointer takes one step back as erasing an element skips the immediate element in the container

      // std::cout << "Players remaining: " << std::endl;
      // for (_players_iter = _active_players.begin(); _players_iter != _active_players.end(); _players_iter ++){
      //   Player temp = *_players_iter;
      //   std::cout << temp.show_name() << std::endl;
      // }
    }

    else{
      std::cerr << "Invalid response. Please try again." << std::endl;
    }
  }

  std::cout << "\nChecking to go to next round...\n" << std::endl;

  if (_call_counter != _active_players.size()){
    _call_counter = 0;
    bet(amount,raise_unit);
  }
  // std::cout << "Size of active players: " << _active_players.size() << std::endl;
  // int i = 1;
  // for(_players_iter = _active_players.begin(); _players_iter != _active_players.end(); _players_iter++){
  //
  //   std::cout << "In for loop..." << "i = " << i << std::endl;
  //
  //   Player check = *_players_iter;
  //   std::cout << "Player " << check.show_name() << std::endl;
  //   if (check.get_pot() != amount){ // if not all Player objects have the same amount in pot, betting continues until every Player object called or all but one folded
  //     std::cout << "Not level i: " << i << std::endl;
  //     bet(amount,raise_unit);
  //   }
  //   i++;
  // }

}

// void Game::bet_next_round(int &amount, int raise_unit){ // checks if it is valid to move to next round by ensuring all Player objects have the same call amount in their own pot
//   for(_players_iter = _active_players.begin(); _players_iter != _active_players.end(); _players_iter++){
//     Player check = *_players_iter;
//     if (check.get_pot() != amount && _call_counter != _active_players.size()){
//       bet(amount,raise_unit);
//     }
//   }
//
// }

void Game::deal_pocket(Deck &deck){ // deal pocket cards to each player

  for(int i=0;i<_active_players.size(); i++){ // iterating through every player
    for (int j = 0; j < 2; j++){ // deals two cards

      Card temp_card = deck.get_top(); // gets the top card from game_deck Deck
      _active_players[i].deal(temp_card); // pushes top card of game deck into player's method of dealing pocket cards
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
  Player winner = _active_players[j]; // assume the first Player object in the _player container is the winner

  for (int i =j+1; i < _active_players.size(); i++){
    if(winner.get_score() <= _active_players[i].get_score()){
      if (winner.get_score() == _active_players[i].get_score()){ // potentially a draw
        draw = true;

      }

      else{ // the candidate winner has the lower score, transfer the information of the candidate winner to the winner object
        winner = _active_players[i]; // let the winner be the i'th Player object which has the presently highest score
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

    for(int p = 0; p < _active_players.size(); p++){
      if(_active_players[p].get_score() == winner.get_score()){ // prints those who share the same score
        std::cout << _active_players[p].show_name() << std::endl;
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
