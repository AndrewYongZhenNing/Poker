#include "poker.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GAME CLASS

Game::Game(){ // upon initialising, set number of players (Player objects), create a Deck (object) and deal cards to Player objects

  std::cout << "Welcome!" << std::endl;

  while(!question){
    std::cout << "\nWould you like to play a game of Poker (p) or would you like to review a statistical analysis of the game(s)? (p/s)";
    std::cin >> _response;

    if (_response == 'p'){

      while(!question){

        std::cout << "\nWould you like to include AI?(y/n)\n";
        std::cin >>_response;


        if(_response == 'y'){ // include two AI
          AI p1 = AI("Archimedes");
          AI p2 = AI("Leibniz");
          _players.push_back(p1);
          _players.push_back(p2);
          question = true;
        }

        else if(_response == 'n'){
          question = true;
        }

        else{
          std::cerr << "Invalid command. Please enter either y or n." << std::endl;

        }
      }

      std::cout << "_players with AI in:" << _players.size() << std::endl;

      //reinitialise question as false to be used in the next while loop
      question = false;

      while(!question){
        std::cout << "\nPlease enter the number of human players:";
        std::cin >> _number_of_players;

        if(_players.size() == 2){ // AI already included
          if(_number_of_players <0){
              std::cerr << "\nInvalid number. Please ensure to enter a positive integer number that is greater than or equal to 2." << std::endl;
            }

          else if(_number_of_players >7){
            std::cerr << "\nThe numver of players, including AI, exceed the maximum (10). Please enter a umber less than or equal to 7." << std::endl;
          }

          else{
            question = true;
          }

        }
        else if(_players.size() == 0){ // no AI present
          if(_number_of_players <2){
            if (_players.size() == 0){ // there are no AI in the game waiting
      				std::cerr << "\nInvalid number of players, please ensure to enter a positive integer number that is greater than or equal to 2." << std::endl;
      			}
      			else if (_players.size() != 0){
      				question = true;
      			}
          }

          else if(_number_of_players >1 && _number_of_players < 11){
            question = true;
          }

          else if(_number_of_players>10){
            std::cerr << "\nThe number of players exceed the maximum (10). Please enter a number less than or equal to 10." << std::endl;
          }

          else{
            std::cerr << "Invalid command. Please enter an integer number." << std::endl;
          }
        }
      }

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

      // start(); //starts the actual dynamic of the game

      // Uncomment below to start a full game
      while(_players.size() > 1){ // pushes back first Player object in _players and _active_players container at the start of each game such that the dealer 'button' rotates around the table
        _total++; // keeps track of how many rounds have passed: for fun
        std::cout << "Number of players in game: " << _active_players.size() << std::endl;
        std::cout << "Total number of players remaining: " << _players.size() << std::endl;
        _players.push_back(_players[0]);
        _players.erase(_players.begin());
        _active_players.push_back(_active_players[0]);
        _active_players.erase(_active_players.begin()); // erase the Player object that was was the front to avoid duplication
        start();

      }

      std::cout << "Game ended" << std::endl;

      if(_players.size() == 1){ // one Player object remaining in the waiting
        std::cout << "Congratulations!\nThe overall winner of this game is Player " << _active_players[0].show_name() << "!" << std::endl;
        std::cout << "Total rounds played: " << _total << std::endl;
      }
      question = true;
    }

    else if(_response == 's'){
      simulation();
      question = false;
      while(!question){
        std::cout << "Run simulation again?(y/n)";
        std::cin>> _response;
        if(_response == 'y'){
          simulation();
          question = true;
        }

        else if(_response == 'n'){
          std::cout << "Thank you for using the simulation. Please enjoy the game." << std::endl;
          question = true;
        }

        else{
          std::cerr << "Invalid response. Please enter either y or n." << std::endl;
        }

      }
    }

    else{
      std::cerr << "Invalid command. Please enter either s for simulation or p for play." << std::endl;

    }
  }

}

Game::~Game(){};

void Game::start(){

  Deck game_deck = Deck(); //initialises a Deck (object) of cards for gameplay

  std::cout << "Shuffling deck...\n" << std::endl;

  game_deck.shuffle();

  std::cout << "Deck shuffled" << std::endl;

  std::cout << "Players remaining: " << std::endl;

  for (_players_iter = _active_players.begin(); _players_iter != _active_players.end(); _players_iter++){
    Player temp = *_players_iter;
    std::cout << temp.show_name() << std::endl;
  }

  // last two Player objects of the game are Dealer, Small and Big Blind respectively
  std::cout << " \nSmall Blind: " << _active_players.rbegin()[1].show_name() << " \nBig Blind: " << _active_players.rbegin()[0].show_name() << std::endl;
  std::cout << "\nDealing pocket cards to players...\n" << std::endl;

  deal_pocket(game_deck); // starts dealing each player their pocket cards

  //BETTING HAPPENS HERE
  std::cout << "\nBetting begins: " << std::endl;

  int call_amount = 0; // a reference amount of raise in each round

  //Last and penultimate Player objects in the _active_players container are the big and small blind respectively
  _active_players.rbegin()[1].bet(_small_blind);
  _active_players.rbegin()[0].bet(_big_blind);

  call_amount += _big_blind;

  bet(call_amount,_big_blind); // pre-flop betting happens in a for loop in here

  deal_flop(game_deck);

  std::cout << "" << std::endl;

  bet(call_amount,_big_blind); // flop betting happens in a for loop in here

  deal_turn(game_deck);

  std::cout << "" << std::endl;

  bet(call_amount,2*_big_blind); // post flop betting happens in a for loop in here

  deal_river(game_deck);

  std::cout << "" << std::endl;

  bet(call_amount,2*_big_blind); // post flop betting happens in a for loop in here

  std::cout << "\n" << std::endl;

  // all the community cards are now on the table, now determine rank

  for (int i = 0; i < _active_players.size(); i++){
    Hand(_active_players[i],_board); // takes in Player object's pocket cards and the community cards to go through evaluation

  }

  declare_winner(); // declares the winner and ends the game
  std::cout << "\n" << std::endl;

  _board.clear();

  for(int i =0; i < _players.size(); i++){
    if(_players[i].get_bankroll() <= _big_blind){
      std::cout << "Player " << _players[i].show_name() <<" has insufficient funds to continue into the next round. By default, Player " << _players[i].show_name() <<" has been discontinued from the game." << std::endl;
      _players.erase(_players.begin()+i);
      i--; // this is to ensure that the pointer does not skip a Player object upon erasing one;
    }
    //for human players
    if(!_players[i].are_you_AI()){
      std::cout <<"Player "<< _players[i].show_name() << ":\nContinue to next round?(y/n)";
      std::cin >> _response;

      if(_response == 'n'){
        std::cout << "Would you like to quit? (Note: you get to keep your remainder bankroll but can no longer continue in this game.)\n(y/n)";
        std::cin >> _response;
        if(_response == 'y'){ // remove Player object from _players container - Player object no longer participates in any of the games
          _players.erase(_players.begin()+i);
          _active_players.erase(_active_players.begin()+i);

          i--;

        }
      }
    }
  }

  // Re-enter folded Player objects before next round
  if(_active_players.size() < _players.size()){
    _active_players.clear();
    for(int i = 0; i < _players.size(); i++){
      _active_players.push_back(_players[i]);
    }
  }

}

void Game::show_players(){ // test purposes: show how many players are in the game

  for (_players_iter = _players.begin(); _players_iter != _players.end(); _players_iter++){

    Player temp = *_players_iter;
    temp.show_name();

  }

}

void Game::bet(int &amount, int raise_unit){

  for (int i = 0; i < _active_players.size(); i++){ // for every Player object in _active_players

    if(_call_counter != _active_players.size()){ // whilst there are outstanding raises, loop this if statement

      if (_active_players[i].are_you_AI()){ // AI Player objects

        if(_active_players[i].get_bankroll() > amount){

          //DO SIMULATION HERE
          std::cout << _active_players[i].show_name() << " is thinking..." << std::endl;
          std::vector<Card> temp = _active_players[i].get_pocket(); // temporary hold the pocket Card objects AI has, to be fed into  simulation method
          // simulation_start(temp[0],temp[1],'s',1000); // set it to 'g' (game) mode, where it does not print out statements, and let simulation run over 10000 times
          // if (probability > 70){ //bet aggressively
          //
          // }
          //
          // else if(probability <=70 && probability > 30){
          //
          // }
          //
          // else if(probability < 5){
          //   std::cout << _active_players[i].show_name() << " has folded." << std::endl;
          //   _community_pot += _active_players[i].get_pot(); // appends whatever that is in the folded Player object's pot into the community pot
          //   _active_players.erase(_active_players.begin()+i); //removes current Player object from the container of active Player objects; will rejoin in the subsequent games
          //   i --; // this is to ensure that the pointer takes one step back as erasing an element skips the immediate element in the container
          // }

          _active_players[i].call(amount);
          _active_players[i].show_bankroll();
          _call_counter ++;
        }
        else if(_active_players[i].get_bankroll() < amount){
          std::cout << "Insufficient funds as call amount is greater than available bankroll. Player " << _active_players[i].show_name() << " is eliminated from the game." << std::endl;
          _community_pot += _active_players[i].get_pot(); // appends whatever that is in the folded Player object's pot into the community pot
          _community_pot += _active_players[i].get_bankroll(); // takes whatever that is left in the Player object's _bankroll
          _active_players.erase(_active_players.begin()+i); //removes current Player object from the container of active Player objects
          _players.erase(_players.begin()+i); // remove current Player object from the container of waiting Player objects since it no longer has enough funds to play
          i--; // this is to ensure that the pointer takes one step back as erasing an element skips the immediate element in the container
        }

      }

      else if(!_active_players[i].are_you_AI()){ // human Player objects
        //Clear screen for Windows with system()
        // system("cls");
        //Clear screen for Linux with ANSI code
        std::cout << "\033[2J\033[1;1H";

        if(_board.size() == 0){
          std::cout << "\nPre-flop betting." << std::endl;
        }
        else if(_board.size() == 3){
          std::cout << "\nCommunity cards at flop:" << std::endl;
          show_board();
        }
        else if(_board.size() == 4){
          std::cout << "\nCommunity cards at turn:" << std::endl;
          show_board();
        }
        else if(_board.size() == 5){
          std::cout << "\nCommunity cards at river:" << std::endl;
          show_board();
        }

        std::cout << "\n" << std::endl;
        _active_players[i].show_pocket();
        _active_players[i].show_bankroll();
        std::cout << "\n" << std::endl;

        std::cout << "Would you like to call/check(c), raise(r), or fold(f)?\nEnter your command (c,r or f)\n";
        std::cin >> _response;

        //call
        if(_response == 'c'){// call: match with the current raised value
          if(_active_players[i].get_bankroll() >= amount){
            _active_players[i].call(amount);
            _active_players[i].show_bankroll();
            _call_counter ++;
          }

          else{ // Player object has insufficient funds, must remove from active AND waiting container
            std::cout << "\nInsufficient funds as call amount is greater than available bankroll. Player " << _active_players[i].show_name() << " is eliminated from the game." << std::endl;
            _community_pot += _active_players[i].get_pot(); // appends whatever that is in the folded Player object's pot into the community pot
            _community_pot += _active_players[i].get_bankroll(); // takes whatever that is left in the Player object's _bankroll
            _active_players.erase(_active_players.begin()+i); //removes current Player object from the container of active Player objects
            i--; // this is to ensure that the pointer takes one step back as erasing an element skips the immediate element in the container

          }

        }

        // raise
        else if(_response == 'r'){

          amount+= raise_unit; // raise by one unit of big blind
          _active_players[i].raise_(amount);
          _active_players[i].show_bankroll();
          _call_counter = 0;
        }

        // fold
        else if(_response == 'f'){
          // char fold_response;
          // std::cout << "You selected fold(f), are you sure?"
          std::cout << "Player " << _active_players[i].show_name() << " has folded." << std::endl;
          _community_pot += _active_players[i].get_pot(); // appends whatever that is in the folded Player object's pot into the community pot
          _active_players.erase(_active_players.begin()+i); //removes current Player object from the container of active Player objects; will rejoin in the subsequent games
          i --; // this is to ensure that the pointer takes one step back as erasing an element skips the immediate element in the container

          if(_active_players.size() == 1){
            std::cout << "Only one remaining player." << _active_players[0].show_name() << " is the winner of the round!" << std::endl;
          }

        }

        else{
          std::cerr << "Invalid response. Please try again." << std::endl;
        }
      }
    }


    else{
      std::cout << "Off to next round." << std::endl;

    }

  }

  std::cout << "\nChecking to go to next round...\n" << std::endl;

  if (_call_counter != _active_players.size()){
    // _call_counter = 0;
    bet(amount,raise_unit);
  }

  _call_counter = 0;
}

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

void Game::declare_winner(){

  int j = 0;
  bool draw = false;
  Player winner = _active_players[j]; // assume the first Player object in the _player container is the winner

  for(j; j<_active_players.size(); j++){ // puts all Player objects' pot into a community pot to be claimed by winner
    _community_pot += _active_players[j].get_pot();
    _active_players[j].clear_pot();

  }

  j = 0;  // reinitialises j as 0 again

  for (int i =j+1; i < _active_players.size(); i++){

    if(winner.get_score() <= _active_players[i].get_score()){

      if (winner.get_score() == _active_players[i].get_score()){ // potentially a draw

        std::vector<Card> winner_hand = winner.get_hand();
        std::vector<Card> contender_hand = _active_players[i].get_hand();

        //evaluate High Card draw
        if(winner.get_score() == 1){ // High Card draw
          if(winner_hand[4].getValue() < contender_hand[4].getValue()){ // check for highest High Card value
            winner = _active_players[i];
            std::cout << winner.show_name() << std::endl;
          }

          else if(winner_hand[4].getValue() == contender_hand[4].getValue()){ // if equivalent, check for second highest High Card value
            //jump straight to first kicker
            if (winner_hand[3].getValue() < contender_hand[3].getValue()){
              winner = _active_players[i];
              std::cout << winner.show_name() << std::endl;
            }

            else if(winner_hand[3].getValue() == contender_hand[3].getValue()){ // if equivalent, check for third highest High Card value
              // consider second kicker
              if (winner_hand[2].getValue() < contender_hand[2].getValue()){
                winner = _active_players[i];
                std::cout << winner.show_name() << std::endl;
              }

              else if(winner_hand[2].getValue() == contender_hand[3].getValue()){ // if equivalent, check for fourth highest High Card value
                // consider final kicker
                if(winner_hand[1].getValue() < contender_hand[1].getValue()){
                  winner = _active_players[i];
                  std::cout << winner.show_name() << std::endl;
                }

                else if(winner_hand[1].getValue() == contender_hand[1].getValue()){ // if equivalent, check for last High Card value
                  if(winner_hand[0].getValue() < contender_hand[0].getValue()){
                    winner = _active_players[i];
                    std::cout << winner.show_name() << std::endl;
                  }

                  else if(winner_hand[0].getValue() == contender_hand[0].getValue()){ //
                    draw = true;
                  }
                }
              }
            }
          }
        }

        //evaluate 1-Pair draw
        else if(winner.get_score() == 2){ //1-Pair draw
          //check if pair value is the same

          if(winner_hand[0].getValue() < contender_hand[0].getValue()){
            winner = _active_players[i];
            std::cout << winner.show_name() << std::endl;
          }

          else if(winner_hand[0].getValue() == contender_hand[0].getValue()){ // if Pair values are the same
            //jump straight to first kicker
            if (winner_hand[4].getValue() < contender_hand[4].getValue()){
              winner = _active_players[i];
              std::cout << winner.show_name() << std::endl;
            }

            else if(winner_hand[4].getValue() == contender_hand[4].getValue()){ // if first Kicker is equivalent
              // consider second kicker
              if (winner_hand[3].getValue() < contender_hand[3].getValue()){
                winner = _active_players[i];
                std::cout << winner.show_name() << std::endl;
              }

              else if(winner_hand[3].getValue() == contender_hand[3].getValue()){ // if seond Kicker is equivalent
                // consider final kicker
                if(winner_hand[2].getValue() < contender_hand[2].getValue()){
                  winner = _active_players[i];
                  std::cout << winner.show_name() << std::endl;
                }

                else if(winner_hand[2].getValue() == contender_hand[2].getValue()){
                  draw = true;
                }
              }
            }
          }
        }

        //evaluate 2-Pair draw
        else if(winner.get_score() == 3){
          if(winner_hand[2].getValue() < contender_hand[2].getValue()){ // check second Pair
            winner = _active_players[i];
            std::cout << winner.show_name() << std::endl;
          }

          else if(winner_hand[2].getValue() == contender_hand[2].getValue()){ // if Pair values are the same
            if(winner_hand[0].getValue() < contender_hand[0].getValue()){ // check first Pair
              winner = _active_players[i];
              std::cout << winner.show_name() << std::endl;
            }

            else if(winner_hand[0].getValue() == contender_hand[0].getValue()){ // if Pair values are the same
              if(winner_hand[4].getValue() < contender_hand[4].getValue()){ // check kicker
                winner = _active_players[i];
                std::cout << winner.show_name() << std::endl;
              }

              else if(winner_hand[4].getValue() == contender_hand[4].getValue()){
                draw = true;
              }
            }
          }
        }

        //evaluate Three Kind draw
        else if(winner.get_score() == 4){
          if(winner_hand[0].getValue() < contender_hand[0].getValue()){ // check second Pair
            winner = _active_players[i];
            std::cout << winner.show_name() << std::endl;
          }

          else if(winner_hand[0].getValue() == contender_hand[0].getValue()){ // if Pair values are the same
            if(winner_hand[4].getValue() < contender_hand[4].getValue()){ // check first Pair
              winner = _active_players[i];
              std::cout << winner.show_name() << std::endl;
            }

            else if(winner_hand[4].getValue() == contender_hand[4].getValue()){ // if Pair values are the same
              if(winner_hand[3].getValue() < contender_hand[3].getValue()){ // check first Pair
                winner = _active_players[i];
                std::cout << winner.show_name() << std::endl;
              }
              else if(winner_hand[3].getValue() == contender_hand[3].getValue()){ // if Pair values are the same
                draw = true;
              }
            }
          }
        }

        //evaluate Straight/Flush/Straight Flush draw (as these ranks have the same 5-card condition, hence can be evaluated by the same logic statement)
        else if(winner.get_score() == 5 || winner.get_score() == 6 || winner.get_score() == 9){
          if(winner_hand[4].getValue() < contender_hand[4].getValue()){ // check second Pair
            winner = _active_players[i];
            std::cout << winner.show_name() << std::endl;
          }

          else if(winner_hand[4].getValue() == contender_hand[4].getValue()){ // if Pair values are the same
            if(winner_hand[3].getValue() < contender_hand[3].getValue()){ // check first Pair
              winner = _active_players[i];
              std::cout << winner.show_name() << std::endl;
            }
            else if(winner_hand[3].getValue() == contender_hand[3].getValue()){ // if Pair values are the same
              if(winner_hand[2].getValue() < contender_hand[2].getValue()){ // check first Pair
                winner = _active_players[i];
                std::cout << winner.show_name() << std::endl;
              }
              else if(winner_hand[2].getValue() == contender_hand[2].getValue()){ // if Pair values are the same
                if(winner_hand[1].getValue() < contender_hand[1].getValue()){ // check first Pair
                  winner = _active_players[i];
                  std::cout << winner.show_name() << std::endl;
                }
                else if(winner_hand[1].getValue() == contender_hand[1].getValue()){ // if Pair values are the same
                  if(winner_hand[0].getValue() < contender_hand[0].getValue()){ // check first Pair
                    winner = _active_players[i];
                    std::cout << winner.show_name() << std::endl;
                  }
                  else if(winner_hand[0].getValue() == contender_hand[0].getValue()){ // check first Pair
                    draw = true;
                  }
                }
              }
            }
          }
        }

        //evaluate Full House draw
        else if(winner.get_score() == 7){
          if(winner_hand[0].getValue() < contender_hand[0].getValue()){ // check Three Kind value
            winner = _active_players[i];
            std::cout << winner.show_name() << std::endl;
          }

          else if(winner_hand[0].getValue() == contender_hand[0].getValue()){ // if Pair values are the same
            if(winner_hand[4].getValue() < contender_hand[4].getValue()){ // check first Pair
              winner = _active_players[i];
              std::cout << winner.show_name() << std::endl;
            }
            else if(winner_hand[4].getValue() == contender_hand[4].getValue()){ // check first Pair
              draw = true;
            }
          }
        }

        // evaluate Four Kind draw
        else if(winner.get_score() == 8){
          if(winner_hand[0].getValue() < contender_hand[0].getValue()){ // check second Pair
            winner = _active_players[i];
            std::cout << winner.show_name() << std::endl;
          }

          else if(winner_hand[0].getValue() == contender_hand[0].getValue()){ // if Pair values are the same
            if(winner_hand[4].getValue() < contender_hand[4].getValue()){ // check first Pair
              winner = _active_players[i];
              std::cout << winner.show_name() << std::endl;
            }
            else if(winner_hand[4].getValue() == contender_hand[4].getValue()){ // check first Pair
              draw = true;
            }
          }
        }

      }

      else{ // the candidate winner has the lower score, transfer the information of the candidate winner to the winner object
        // _active_players[i].claim_pot(_community_pot); // actual winner Player object claims the pot, not the object called winner
        // std::cout << _active_players[i].show_name();
        // _active_players[i].show_bankroll();
        winner = _active_players[i]; // let the winner be the i'th Player object which has the presently highest score
        draw = false; // put this line here just in case previous there were cases where other Plyers objects have the same score
      }

    }

  }

  if (!draw){
    std::cout << "Congratulations!\nThe winner of round " << _total << " is: " << winner.show_name() << "\n" << std::endl;
    for (int i = 0; i < _active_players.size(); i++){
      if(_active_players[i].show_name() == winner.show_name()){
        _active_players[i].claim_pot(_community_pot);
      }
    }

    // winner.show_bankroll();
    //winner.collect_pot(_pot); // increases the winner's bankroll by the amount of bet on the particular round

  }

  else if (draw){

    for(int r = 0; r < _active_players.size(); r++){
      //
    }
    std::cout << "It's a draw between:" << std::endl;

    for(int p = 0; p < _active_players.size(); p++){
      if(_active_players[p].get_score() == winner.get_score()){ // prints those who share the same score
        std::cout << _active_players[p].show_name() << std::endl;
      }
    }
  }

  for(int i = 0; i < _active_players.size(); i++){

    std::cout << "Player " << _active_players[i].show_name()<< "- ";
    _active_players[i].show_bankroll();
    std::cout << "" << std::endl;
  }
}

void Game::simulation(){

  std::cout << "Begin simulation." << std::endl;

  // User selection
  std::cout << "Please select a starting hand of your choice:\nUse the abbreviation H,S,C,D for the suit and 2,3,4,5,6,7,8,9,10,J,Q,K,A for the face value." << std::endl;
  // Player dummy = Player("Archimedes");
  int val = 0;
  std::vector<Card> temp_pocket;

  for(int i = 0; i<2; i++){
    val = 0;
    question = false;
    while (!question){
      std::cout << "Card #" << i+1 << ":" << std::endl;
      std::cout << "Suit:";
      std::cin>> _face;

      if (_face == 'h' || _face == 'H'){
        question = true;
      }

      else if(_face == 'd' || _face == 'D'){
        question = true;
      }
      else if(_face == 'c' || _face == 'C'){
        question = true;
      }
      else if(_face == 's' || _face == 'S'){
        question = true;
      }

      else{
        std::cerr << _face << " is an invalid suit. Please enter using the abbreviation provided: H,S,D,C." << std::endl;
        question = false;
      }
    }

    question = false;
    while(!question){
      std::cout << "Face Value:";
      std::cin >> _value;

      question = false;

      if (_value == "2"){
        val = 2;
        question = true;
      }
      else if(_value == "3"){
        val = 3;
        question = true;
      }
      else if(_value == "4"){
        val = 4;
        question = true;
      }
      else if(_value == "5"){
        val = 5;
        question = true;
      }
      else if(_value == "6"){
        val = 6;
        question = true;
      }
      else if(_value == "7"){
        val = 7;
        question = true;
      }
      else if(_value == "8"){
        val = 8;
        question = true;
      }
      else if(_value == "9"){
        val = 9;
        question = true;
      }
      else if(_value == "10"){
        val = 10;
        question = true;
      }
      else if(_value == "J" || _value == "j"){ // case (in)sensitive
        val = 11;
        question = true;
      }
      else if(_value == "Q" || _value == "q"){// case (in)sensitive
        val = 12;
        question = true;
      }
      else if(_value == "K" || _value == "k"){// case (in)sensitive
        val = 13;
        question = true;
      }
      else if(_value == "A" || _value == "a"){// case (in)sensitive
        val = 14;
        question = true;
      }

      else{
        std::cerr << "Invalid face value. Please enter a face value between 2 to Ace using the abbreviation below: \n2,3,4,5,6,7,8,9,10,J,Q,K,A" << std::endl;
        question = false;
      }
    }

    //Create Card object to append into dummy's pocket cards.
    Card c = Card(_face,val);
    temp_pocket.push_back(c);
  }

  std::cout << "Set number of simulations: ";
  std::cin >> _limit;

  //Selected starting hand for testing
  Card c1 = temp_pocket[0];
  Card c2 = temp_pocket[1];

  simulation_start(c1,c2,'s',_limit); // command == 's' implies this is strictly a simulation study

}

float Game::simulation_start(Card c1, Card c2, char command, int limit){
  float win_percentage = 0;

  AI dummy = AI("Hamilton");
  dummy.deal(c1);
  dummy.deal(c2);

  _total = 0;

  while(_total < limit){

    if(command = 's'){ //'s' for simulation run
      std::cout << "Round: " << _total + 1 << std::endl;
    }


    Deck simulation_deck = Deck();

    simulation_deck.remove_card(c1);
    simulation_deck.remove_card(c2); // working fine - Deck printed out with AH and KH missing

    // Now randomise the deck
    simulation_deck.shuffle();

    AI foe = AI("Lagrange");
    _active_players.push_back(foe);
    deal_pocket(simulation_deck); // allow the foe to be given random cards before push_back of test
    _active_players.push_back(dummy);

    deal_flop(simulation_deck);
    deal_turn(simulation_deck);
    deal_river(simulation_deck);

    for (int i = 0; i < _active_players.size(); i++){
      Hand(_active_players[i],_board); // takes in Player object's pocket cards and the community cards to go through evaluation

    }

    s_declare_winner(_win,command);

    _total ++;

    foe.empty_pocket();
    _board.clear();
    _active_players.clear();

  }
  //Winning percentage
  win_percentage = (_win*1./_total )*100;

  if(command = 's'){
    std::cout << "Win: " << win_percentage << "%" << std::endl;
  }

  return win_percentage;

}

void Game::s_declare_winner(int &win, char command){

  int j = 0;
  bool draw = false;
  Player winner = _active_players[j]; // assume the first Player object in the _player container is the winner

  for (int i =j+1; i < _active_players.size(); i++){

    if(winner.get_score() <= _active_players[i].get_score()){

      if (winner.get_score() == _active_players[i].get_score()){ // potentially a draw

        std::vector<Card> winner_hand = winner.get_hand();
        std::vector<Card> contender_hand = _active_players[i].get_hand();

        //evaluate High Card draw
        if(winner.get_score() == 1){ // High Card draw
          if(winner_hand[4].getValue() < contender_hand[4].getValue()){ // check for highest High Card value
            winner = _active_players[i];
            std::cout << winner.show_name() << std::endl;
          }

          else if(winner_hand[4].getValue() == contender_hand[4].getValue()){ // if equivalent, check for second highest High Card value
            //jump straight to first kicker
            if (winner_hand[3].getValue() < contender_hand[3].getValue()){
              winner = _active_players[i];
              std::cout << winner.show_name() << std::endl;
            }

            else if(winner_hand[3].getValue() == contender_hand[3].getValue()){ // if equivalent, check for third highest High Card value
              // consider second kicker
              if (winner_hand[2].getValue() < contender_hand[2].getValue()){
                winner = _active_players[i];
                std::cout << winner.show_name() << std::endl;
              }

              else if(winner_hand[2].getValue() == contender_hand[3].getValue()){ // if equivalent, check for fourth highest High Card value
                // consider final kicker
                if(winner_hand[1].getValue() < contender_hand[1].getValue()){
                  winner = _active_players[i];
                  std::cout << winner.show_name() << std::endl;
                }

                else if(winner_hand[1].getValue() == contender_hand[1].getValue()){ // if equivalent, check for last High Card value
                  if(winner_hand[0].getValue() < contender_hand[0].getValue()){
                    winner = _active_players[i];
                    std::cout << winner.show_name() << std::endl;
                  }

                  else if(winner_hand[0].getValue() == contender_hand[0].getValue()){ //
                    draw = true;
                  }
                }
              }
            }
          }
        }

        //evaluate 1-Pair draw
        else if(winner.get_score() == 2){ //1-Pair draw
          //check if pair value is the same
          if(winner_hand[0].getValue() < contender_hand[0].getValue()){
            winner = _active_players[i];
            std::cout << winner.show_name() << std::endl;
          }

          else if(winner_hand[0].getValue() == contender_hand[0].getValue()){ // if Pair values are the same
            //jump straight to first kicker
            if (winner_hand[4].getValue() < contender_hand[4].getValue()){
              winner = _active_players[i];
              std::cout << winner.show_name() << std::endl;
            }

            else if(winner_hand[4].getValue() == contender_hand[4].getValue()){ // if first Kicker is equivalent
              // consider second kicker
              if (winner_hand[3].getValue() < contender_hand[3].getValue()){
                winner = _active_players[i];
                std::cout << winner.show_name() << std::endl;
              }

              else if(winner_hand[3].getValue() == contender_hand[3].getValue()){ // if seond Kicker is equivalent
                // consider final kicker
                if(winner_hand[2].getValue() < contender_hand[2].getValue()){
                  winner = _active_players[i];
                  std::cout << winner.show_name() << std::endl;
                }

                else if(winner_hand[2].getValue() == contender_hand[2].getValue()){
                  draw = true;
                }
              }
            }
          }
        }

        //evaluate 2-Pair draw
        else if(winner.get_score() == 3){
          if(winner_hand[2].getValue() < contender_hand[2].getValue()){ // check second Pair
            winner = _active_players[i];
            std::cout << winner.show_name() << std::endl;
          }

          else if(winner_hand[2].getValue() == contender_hand[2].getValue()){ // if Pair values are the same
            if(winner_hand[0].getValue() < contender_hand[0].getValue()){ // check first Pair
              winner = _active_players[i];
              std::cout << winner.show_name() << std::endl;
            }

            else if(winner_hand[0].getValue() == contender_hand[0].getValue()){ // if Pair values are the same
              if(winner_hand[4].getValue() < contender_hand[4].getValue()){ // check kicker
                winner = _active_players[i];
                std::cout << winner.show_name() << std::endl;
              }

              else if(winner_hand[4].getValue() == contender_hand[4].getValue()){
                draw = true;
              }
            }
          }
        }

        //evaluate Three Kind draw
        else if(winner.get_score() == 4){
          if(winner_hand[0].getValue() < contender_hand[0].getValue()){ // check second Pair
            winner = _active_players[i];
            std::cout << winner.show_name() << std::endl;
          }

          else if(winner_hand[0].getValue() == contender_hand[0].getValue()){ // if Pair values are the same
            if(winner_hand[4].getValue() < contender_hand[4].getValue()){ // check first Pair
              winner = _active_players[i];
              std::cout << winner.show_name() << std::endl;
            }

            else if(winner_hand[4].getValue() == contender_hand[4].getValue()){ // if Pair values are the same
              if(winner_hand[3].getValue() < contender_hand[3].getValue()){ // check first Pair
                winner = _active_players[i];
                std::cout << winner.show_name() << std::endl;
              }
              else if(winner_hand[3].getValue() == contender_hand[3].getValue()){ // if Pair values are the same
                draw = true;
              }
            }
          }
        }

        //evaluate Straight/Flush/Straight Flush draw (as these ranks have the same 5-card condition, hence can be evaluated by the same logic statement)
        else if(winner.get_score() == 5 || winner.get_score() == 6 || winner.get_score() == 9){
          if(winner_hand[4].getValue() < contender_hand[4].getValue()){ // check second Pair
            winner = _active_players[i];
            std::cout << winner.show_name() << std::endl;
          }

          else if(winner_hand[4].getValue() == contender_hand[4].getValue()){ // if Pair values are the same
            if(winner_hand[3].getValue() < contender_hand[3].getValue()){ // check first Pair
              winner = _active_players[i];
              std::cout << winner.show_name() << std::endl;
            }
            else if(winner_hand[3].getValue() == contender_hand[3].getValue()){ // if Pair values are the same
              if(winner_hand[2].getValue() < contender_hand[2].getValue()){ // check first Pair
                winner = _active_players[i];
                std::cout << winner.show_name() << std::endl;
              }
              else if(winner_hand[2].getValue() == contender_hand[2].getValue()){ // if Pair values are the same
                if(winner_hand[1].getValue() < contender_hand[1].getValue()){ // check first Pair
                  winner = _active_players[i];
                  std::cout << winner.show_name() << std::endl;
                }
                else if(winner_hand[1].getValue() == contender_hand[1].getValue()){ // if Pair values are the same
                  if(winner_hand[0].getValue() < contender_hand[0].getValue()){ // check first Pair
                    winner = _active_players[i];
                    std::cout << winner.show_name() << std::endl;
                  }
                  else if(winner_hand[0].getValue() == contender_hand[0].getValue()){ // check first Pair
                    draw = true;
                  }
                }
              }
            }
          }
        }

        //evaluate Full House draw
        else if(winner.get_score() == 7){
          if(winner_hand[0].getValue() < contender_hand[0].getValue()){ // check Three Kind value
            winner = _active_players[i];
            std::cout << winner.show_name() << std::endl;
          }

          else if(winner_hand[0].getValue() == contender_hand[0].getValue()){ // if Pair values are the same
            if(winner_hand[4].getValue() < contender_hand[4].getValue()){ // check first Pair
              winner = _active_players[i];
              std::cout << winner.show_name() << std::endl;
            }
            else if(winner_hand[4].getValue()== contender_hand[4].getValue()){ // check first Pair
              draw = true;
            }
          }
        }

        // evaluate Four Kind draw
        else if(winner.get_score() == 8){
          if(winner_hand[0].getValue() < contender_hand[0].getValue()){ // check second Pair
            winner = _active_players[i];
            std::cout << winner.show_name() << std::endl;
          }

          else if(winner_hand[0].getValue() == contender_hand[0].getValue()){ // if Pair values are the same
            if(winner_hand[4].getValue() < contender_hand[4].getValue()){ // check first Pair
              winner = _active_players[i];
              std::cout << winner.show_name() << std::endl;
            }
            else if(winner_hand[4].getValue() < contender_hand[4].getValue()){ // check first Pair
              draw = true;
            }
          }
        }

      }

      else{ // the candidate winner has the lower score, transfer the information of the candidate winner to the winner object
        winner = _active_players[i]; // let the winner be the i'th Player object which has the presently highest score
        _active_players[i].claim_pot(_community_pot); // actual winner Player object claims the pot, not the object called winner
        draw = false; // put this line here just in case previous there were cases where other Plyers objects have the same score
      }

    }

  }

  if (!draw){
    if(command == 's'){
      std::cout << "The winner is: " << winner.show_name() << std::endl;
    }

    if(winner.show_name() == _active_players[1].show_name()){
      win++;
    }


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
