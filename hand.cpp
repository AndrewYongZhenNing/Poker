#include "hand.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// HAND CLASS

Hand::Hand(Player &player, std::vector<Card> board){ // evaluates the hands of each player at showdown

  std::cout << "Player " << player.show_name() << " has the following cards: " << std::endl; // displays name of player

  _temp_player = player.get_pocket(); // now temp holds the specific player's pocket cards


  //fill _hand container with player's pocket cards
  for (_temp_iter = _temp_player.begin(); _temp_iter != _temp_player.end(); _temp_iter++){

    Card temp = *_temp_iter;


    temp.show_card();

    _temp_hand.push_back(*_temp_iter); //dereferencing _temp_iter will give one of the two cards in the Player's pockets where the pointer is pointing at

  }

  //fill _hand container with board's community cards
  for (_temp_iter = board.begin();_temp_iter != board.end(); _temp_iter++){

    _temp_hand.push_back(*_temp_iter); // dereferencing _temp_iter will give one of the community cards in the board at game

  }

  // std::cout << "\nThe hand for " << player.show_name() << " is: " << std::endl;
  //
  // // print the Hand to check
  // for (_temp_iter = _temp_hand.begin();_temp_iter != _temp_hand.end(); _temp_iter++){ // testing purposes
  //
  //   Card temp = *_temp_iter;
  //
  //   temp.show_card();
  //
  // }


  // for (_temp_iter = _hand.begin();_temp_iter != _hand.end(); _temp_iter++){ // testing purposes
  //
  //   Card temp = *_temp_iter;
  //
  //   temp.show_card();
  //
  // }

  std::cout << "" << std::endl;

  //sorts and give the Hand object a score
  player.assign_score(evaluate()); // assigns the score to the Player object this Hand is for

  std::cout << "\nThe hand for " << player.show_name() << " is: " << std::endl;
  for (_temp_iter = _hand.begin();_temp_iter != _hand.end(); _temp_iter++){ // testing purposes

    Card temp = *_temp_iter;

    temp.show_card();
  }
  std::cout << "\n" << std::endl;
  player.show_score(); //a method to check if the scores are evaluated properly
  player.get_score();
  player.get_hand(_hand); // passes the _hand container evaluated in Hand class to each Player object

  // Below the hand and pocket containers are cleared for the new game;
  _temp_hand.clear();
  _hand.clear();
  player.empty_pocket();




}

Hand::Hand(Player &player, std::vector<Card> board, char command){ // Simulation hand

    _temp_player = player.get_pocket(); // now temp holds the specific player's pocket cards


    //fill _hand container with player's pocket cards
    for (_temp_iter = _temp_player.begin(); _temp_iter != _temp_player.end(); _temp_iter++){

      Card temp = *_temp_iter;


      // temp.show_card(); //test not needed in simulation

      _temp_hand.push_back(*_temp_iter); //dereferencing _temp_iter will give one of the two cards in the Player's pockets where the pointer is pointing at

    }

    //fill _hand container with board's community cards
    for (_temp_iter = board.begin();_temp_iter != board.end(); _temp_iter++){

      _temp_hand.push_back(*_temp_iter); // dereferencing _temp_iter will give one of the community cards in the board at game

    }

    // std::cout << "\nThe hand for " << player.show_name() << " is: " << std::endl;
    //
    // // print the Hand to check
    // for (_temp_iter = _temp_hand.begin();_temp_iter != _temp_hand.end(); _temp_iter++){ // testing purposes
    //
    //   Card temp = *_temp_iter;
    //
    //   temp.show_card();
    //
    // }


    // for (_temp_iter = _hand.begin();_temp_iter != _hand.end(); _temp_iter++){ // testing purposes
    //
    //   Card temp = *_temp_iter;
    //
    //   temp.show_card();
    //
    // }

    // std::cout << "" << std::endl;

    //sorts and give the Hand object a score
    player.assign_score(s_evaluate()); // assigns the score to the Player object this Hand is for

    // std::cout << "\nThe hand for " << player.show_name() << " is: " << std::endl;
    // for (_temp_iter = _hand.begin();_temp_iter != _hand.end(); _temp_iter++){ // testing purposes
    //
    //   Card temp = *_temp_iter;
    //
    //   temp.show_card();
    // }
    // std::cout << "\n" << std::endl;
    // player.show_score(); //a method to check if the scores are evaluated properly
    player.get_score();
    player.get_hand(_hand); // passes the _hand container evaluated in Hand class to each Player object

    // Below the hand and pocket containers are cleared for the new game;
    _temp_hand.clear();
    _hand.clear();
    player.empty_pocket();


}

Hand::~Hand(){};

int Hand::evaluate(){ // sorts and prints out the sorted Hand

  std::cout << "Evaluate the points of the player" << std::endl;

  std::vector<Card>::iterator sort_iter; // create a sorting iterator
  std::vector<Card> temp_pair;
  int score = 0;
  int position = 0;

  std::cout << "Sorting begins..." << std::endl;
  // sorts _temp_hand in ascending order for easier evaluation
  std::sort(_temp_hand.begin(),_temp_hand.end());

  // prints the sorted hand
  for (sort_iter = _temp_hand.begin();sort_iter != _temp_hand.end(); sort_iter++){ // testing purposes

    Card temp = *sort_iter;

    temp.show_card();

  }

  std::cout << "" << std::endl;

  //Evaluation of Card Rank begins here

  //Checks for Straight Flush
  straight_flush_check();

  //Checks for Flush
  flush_check();

  for(int i = 0; i < _temp_hand.size(); i++){

    // Check for High Card, 1-Pair, 2-Pairs, Three of a Kind, Four of a Kind,
    if(i+1 < _temp_hand.size() && _temp_hand[i].getValue() == _temp_hand[i+1].getValue()){ // is current Card object value same as next Card object value?
      // first condition of i+n < hand.size(), where n is 1,2,3, is to make sure the pointer doesnt exceed the size of the container and hence prevent segmentation fault
      if (i+2 < _temp_hand.size() && _temp_hand[i].getValue() == _temp_hand[i+2].getValue()){ // is current Card object value same as next next Card object value?
        if(i+3 < _temp_hand.size() && _temp_hand[i].getValue() == _temp_hand[i+3].getValue()){ // is current Card object value same as next next NEXT Card object value?
          four_kind = true; // it's a Four of a Kind
          position = i;
          for(position; position < i+4; position++){
            Card temp = _temp_hand[position];
            _hand.push_back(temp);
          }

        }

        else if (i+3 < _temp_hand.size() && _temp_hand[i].getValue() != _temp_hand[i+3].getValue()){ // it's a Three of a Kind
          three_kind = true;
          position = i;
          for(position; position < i+3; position++){
            Card temp = _temp_hand[position];
            _hand.push_back(temp);
          }

        }
        //if the Three Kind is located at the end of the container, confirmed no fourth pair
        else if(i+3 == _temp_hand.size()){
          three_kind = true;
          position = i;
          for(position; position < i+3; position++){
            Card temp = _temp_hand[position];
            _hand.push_back(temp);
          }
        }

      }

      else if(i>0 && _temp_hand[i-1].getValue() != _temp_hand[i].getValue()){ // extra condition to ensure that this is only a Pair IFF it is not equal to the value before it

        //push back for later:
        // pushes back the two cards that makes 1-Pair
        // _pair.push_back(hand[i]);
        // _pair.push_back(hand[i+1]);
        pair +=1;
        position = i;
        for(position; position < i+2; position++){

          Card temp = _temp_hand[position];
          // append Pair Card objects temporarily into temp_pair in case the possibility of Full House
          // if Full House is not available, append temp_pair Card objects into _hand for 1-Pair 2-Pair
          temp_pair.push_back(temp);
          std::sort(temp_pair.begin(),temp_pair.end()); // ensures that it is always in ascending order
          // _hand.push_back(temp);
        }
        // save the erasing and sorting for when it is determined whether or not it is 1-Par or 2-Pairs

        // if (pair >2){ // if there are more
        //   three_kind = true;
        //   pair = 0
        // }

      }

      else if(i ==0){ // it is definitely a Pair
        if(!straight || !straight_flush || !flush || !four_kind){
          pair +=1;
          position = i;

          for(position; position < i+2; position++){
            // std::cout << "Checkpoint 2.1" << std::endl;
            Card temp = _temp_hand[position];
            // append Pair Card objects temporarily into temp_pair in case the possibility of Full House
            // if Full House is not available, append temp_pair Card objects into _hand for 1-Pair 2-Pair
            temp_pair.push_back(temp);
            std::sort(temp_pair.begin(),temp_pair.end()); // ensures that it is always in ascending order
            // _hand.push_back(temp);
          }
        }
      }
    }
    // Check for Straight
    else if(_temp_hand[i+1].getValue() == _temp_hand[i].getValue()+1){ //is the next Card object one value higher than the current Card object?
      if(_temp_hand[i+2].getValue() == _temp_hand[i].getValue()+2){//is the next Card object two value higher than the current Card object?
        if(_temp_hand[i+3].getValue() == _temp_hand[i].getValue()+3){ //is the next Card object three value higher than the current Card object?
          if (_temp_hand[i+4].getValue() == _temp_hand[i].getValue()+4){
            straight = true;// it's a straight
            position = i;

            // if(_temp_hand[i].getValue() == 2){ // if the start of the Straight is a 2, see if there is an Ace in the _temp_hand as well
            //   int count = 0; //ensures that if there are two Ace Card objects, take one and leave for loop
            //   for(int j = 0; j < _temp_hand.size(); j++){
            //     if(count == 0){
            //       if(_temp_hand[j].getValue()== 14){ // switch Ace value from 14 to 1
            //         _temp_hand[j].switch_ace();
            //         Card temp = _temp_hand[j];
            //         _hand.push_back(temp);
            //         count ++; // this ensures that once an Ace has been appended into _hand, take no more and fill it with the rest of the sequence
            //       }
            //     }
            //
            //   }
            //   for(position; position < i+4; position ++){
            //     Card temp = _temp_hand[position];
            //     _hand.push_back(temp);
            //   }
            // }
            //
            // else{ // if the start of the Straight is NOT of value 2, append as normal
            //   for (position; position < i+5; position ++){
            //     Card temp = _temp_hand[position];
            //     _hand.push_back(temp);
            //   }
            // }
            for (position; position < i+5; position ++){ // append the straight Card objects to _hand
                Card temp = _temp_hand[position];
                _hand.push_back(temp);
              }

          }

          else if(_temp_hand[i+4].getValue() != _temp_hand[i].getValue()+4 && _temp_hand[i].getValue()==2 ){ // one last hope: is there an Ace in the _temp_hand?
            int count = 0; //ensures that if there are two Ace Card objects, take one and leave for loop
            for(int j = 0; j < _temp_hand.size(); j++){
              if(count == 0){
                if(_temp_hand[j].getValue()== 14){ // switch Ace value from 14 to 1
                  _temp_hand[j].switch_ace();
                  Card temp = _temp_hand[j];
                  _hand.push_back(temp);
                  count ++; // this ensures that once an Ace has been appended into _hand, take no more and fill it with the rest of the sequence
                  straight = true;
                  position = i;
                }
              }
            }
            if(straight){
              for(position; position < i+4; position ++){
                Card temp = _temp_hand[position];
                _hand.push_back(temp);
            }

            }
          }
        }
      }
    }

    // else{ //it may be a high card
    //
    //   if(_pair.size() == 0){ // only consider High Cards if no Pair is present
    //     _high_card.push_back(hand[i]); //push back the Card objects that could potentially be the high cards
    //   }
    //
    // }

    // std::cout << hand[i].getValue() << " "<< std::flush;
  }

  std::cout << "" << std::endl;

  //assigning score to each possible Hand
  if(straight_flush){
    score = 9;
  }

  else if(four_kind){
    // first remove the Card objects in _temp_hand that are equivalent to those in _hand at the moment
    for(int i =0; i < _temp_hand.size(); i++){

      if (_temp_hand[i].getValue() == _hand[0].getValue()){ // if the Card object in _temp_hand is same as the Card object in _hand
        _temp_hand.erase(_temp_hand.begin()+i); // erase the duplicate Card object in _temp_hand
        i--;
      }
    }

    // append the highest kickers for Three of a Kind
    Card temp = _temp_hand.back();
    _hand.push_back(temp);
    _temp_hand.pop_back();

    score = 8;
  }

  else if(pair >= 1 && three_kind){ //full house
    if (pair >1){ // there is already a 2-Pair in place
      // std::sort(_hand.begin(),_hand.end());
      // _hand.erase(_hand.begin(),_hand.begin()+1); // this removes the first two (smallest-valued) Pair to make room for Full House
      std::cout << "Entering while" << std::endl;
      //reduce the size of temp_pair to two, holding the two Pair
      while(temp_pair.size() != 2){
        temp_pair.erase(temp_pair.begin(),temp_pair.begin()+2);
      }
      std::cout << "Exited while" << std::endl;
    }

    // push back the highest Pair to complete a full house
    //now pair will be at the end of the container, positioned 4th and 5th Card object in _hold
    for (int y= 0; y < temp_pair.size(); y++){
      Card pair_card = temp_pair[y];
      _hand.push_back(pair_card);
    }
    score = 7;
  }

  else if(flush){
    score = 6;
  }

  else if(straight){

    //if the sequence is longer than 5, the program will pick every possible 5-Card sequence and append it to _hand
    // remove the first n elements as they will be of the lowest values
    if(_hand.size() > 5){
      int cut_off = _hand.size() - 5;
      _hand.erase(_hand.begin(),_hand.begin()+cut_off);
    }
    score = 5;
  }

  else if(three_kind){
    // first remove the Card objects in _temp_hand that are equivalent to those in _hand at the moment
    for(int i =0; i < _temp_hand.size(); i++){

      if (_temp_hand[i].getValue() == _hand[0].getValue()){ // if the Card object in _temp_hand is same as the Card object in _hand
        _temp_hand.erase(_temp_hand.begin()+i); // erase the duplicate Card object in _temp_hand
        i--;
      }
    }

    // append two of the highest kickers for Three of a Kind
    for (int i = 0; i <2; i ++){
      Card temp = _temp_hand.back();
      _hand.push_back(temp);
      _temp_hand.pop_back();
    }
    std::sort(_hand.begin()+3,_hand.end());

    score = 4;
  }

  else if(pair >= 2){ // 2-Pairs
    if(pair ==2){ // 2-Pairs case

      // appends Card objects from temp_pair into _hand
      for (int y= 0; y < temp_pair.size(); y++){
        Card pair_card = temp_pair[y];
        _hand.push_back(pair_card);
      }

      //first, remove pair cards from _temp_hand
      for(int i =0; i < _temp_hand.size(); i++){

        if (_temp_hand[i].getValue() == _hand[0].getValue()){ // if the Card object in _temp_hand is same as the Card object in _hand
          _temp_hand.erase(_temp_hand.begin()+i); // erase the duplicate Card object in _temp_hand
          i--;
        }

        else if(_temp_hand[i].getValue() == _hand[2].getValue()){
          _temp_hand.erase(_temp_hand.begin()+i); // erase the duplicate Card object in _temp_hand
          i--;
        }

      }

      //now, _temp_hand is a container full of possible kicker Card object
      int p = 0;
      Card kicker = _temp_hand[p];

      for(int k = p+1; k < _temp_hand.size(); k++){
        if(kicker.getValue() < _temp_hand[k].getValue()){
          kicker = _temp_hand[k]; // switch potential kicker Card object to the new card

        }
      }
      _hand.push_back(kicker);
    }

    else if(pair >2){

      // appends Card objects from temp_pair into _hand
      for (int y= 0; y < temp_pair.size(); y++){
        Card pair_card = temp_pair[y];
        _hand.push_back(pair_card);
      }

      //remove lowest value pair first, then consider the kicker card
      std::sort(_hand.begin(),_hand.end());
      // remove the first Pair because they will have the lowest value
      _hand.erase(_hand.begin(),_hand.begin()+2); // +2 because erase does not include the +i'th element
      for(int i =0; i < _temp_hand.size(); i++){
        // erase the duplicate Card object in _temp_hand
        if (_temp_hand[i].getValue() == _hand[0].getValue()){ // if the Card object in _temp_hand is same as the Card object in _hand
          _temp_hand.erase(_temp_hand.begin()+i);
          i--;
        }

        else if(_temp_hand[i].getValue() == _hand[2].getValue()){
          _temp_hand.erase(_temp_hand.begin()+i); // erase the duplicate Card object in _temp_hand
          i--;
        }

      }

      //now, _temp_hand is a container full of possible kicker Card object
      // int p = 0;
      // std::sort(_temp_hand.begin(), _temp_hand.end());
      Card kicker = *_temp_hand.rbegin(); // let kicker be the last Card object (also the one with the highest value) from the _temp_hand

      // for(int k = p+1; k < _temp_hand.size(); k++){
      //   if(kicker.getValue() < _temp_hand[k].getValue()){
      //     kicker = _temp_hand[k]; // switch potential kicker Card object to the new card
      //
      //   }
      // }
      _hand.push_back(kicker);
    }
    score = 3;
  }

  else if(pair == 1){ // 1-Pair

    // appends Card objects from temp_pair into _hand
    for (int y= 0; y < temp_pair.size(); y++){
      Card pair_card = temp_pair[y];
      _hand.push_back(pair_card);
    }

    //first, remove pair cards from _temp_hand
    for(int i =0; i < _temp_hand.size(); i++){

      if (_temp_hand[i].getValue() == _hand[0].getValue()){ // if the Card object in _temp_hand is same as the Card object in _hand
        _temp_hand.erase(_temp_hand.begin()+i); // erase the duplicate Card object in _temp_hand
        i--;
      }
    }

    for (int j = 0; j <3; j++){
      Card temp = _temp_hand.back();
      _hand.push_back(temp);
      _temp_hand.pop_back();

    }
    std::sort(_hand.begin()+2,_hand.end());

    score = 2;
  }

  else if(pair == 0){ // high card

    for (int i = 0; i <5 ; i++){ // give the Player object 5 high cards such that Player object can compare to other Player objects more than once to determine a winner amongst two high card hands
      Card temp = _temp_hand.back();
      _hand.push_back(temp);
      _temp_hand.pop_back();
    }
    std::sort(_hand.begin(),_hand.end()); // this ensures that the High Card is always at the end of the container
    score = 1;
  }

  // _temp_hand.clear();

  return score;
}

bool Hand::flush_check(){

  char suit_set[4] = {'H', 'C', 'S', 'D'};
  int suit_counter=0; // create a counter to use for each suit
  // int position = 0; // create a variable to track the starting position of the flush in the hand
  char flush_suit = 'n'; // initialise a dummy suit index

  for(int i = 0; i < 4; i++){ // for every suit

    for (int j = 0; j < _temp_hand.size(); j++){ // for every Card object in the container
      Card temp = _temp_hand[j];
      if(temp.getSuit() == suit_set[i]){
        // std::cout << "In flush_check, temp_suit:"<< temp.getSuit() << " suit_set: " << suit_set[i] << std::endl; // for testing purposes
        suit_counter += 1;
        if (suit_counter == 5){
          // position = j-4;
          flush_suit = suit_set[i]; // records the suit that forms a flush in the hand
        }
      }

    }

    if(suit_counter == 5){ // if found a flush, exit immediately
      flush= true;

      // using the recorded flush_suit, get all the highest value flush Card objects
      for(int k = 0; k < _temp_hand.size(); k++){
        Card temp = _temp_hand.rbegin()[k]; // iterate from behind to get the highest value flush
        if(temp.getSuit() == flush_suit && _hand.size() != 5){
          _hand.push_back(temp);
        }
      }
      //ensures flush cards are in ascending order
      std::sort(_hand.begin(),_hand.end());
      // hand.erase(hand.begin(),hand.end()-5);
      return flush;
    }

    else{ // sets suit_counter back to zero if there are less than 5 Card objects of the current suit
      suit_counter = 0;
    }

  }

  if(suit_counter != 5){ // not a flush
    flush = false;
    return flush;
  }

}

void Hand::straight_flush_check(){
  char suit_set[4] = {'H', 'C', 'S', 'D'};
  int suit_counter=0; // create a counter to use for each suit
  int position = 0;
  int count = 0;

  for(int i =0; i < 4; i++){ // check through every Suit

    for (int j = 0; j < _temp_hand.size()-1; j++){ // -1 to ensure that j+1 is still within container size (prevent segmentation fault)

      if (_temp_hand[j].getSuit() == suit_set[i] && _temp_hand[j+1].getSuit() == _temp_hand[j].getSuit() && _temp_hand[j+1].getValue() == _temp_hand[j].getValue()+1){
        suit_counter += 1;

        // this if statement helps to determine the starting position of the straight flush
        // note suit_counter is equals to 3 (rather than 5) because the if statement above has imposed that if the first 4 elements satisfy the condition AND the 5th element is the same as the 4th, the loop would end at the 4th element, so suit_counter will only count 4
        if(suit_counter == 4){ // provided that suit_counter found 5 consecutive Card objects, let the starting position be the current position subtracted by 4
           // position is current minus 3 because j starts from 0 and the nth iteration it is on the (n-1)'th position
          position = j-3;
        }
      }

      else if(suit_counter == 3){// if there are 4 Card objects of consecutive face value and suit
        // by the time it passes the above if loop, j would by the 4th iteration as it has successfully incremented suit_counter 3 times before that corresponds to the 4 consecutive Card objects
        if (_temp_hand[j+1].getSuit() != _temp_hand[j].getSuit() || _temp_hand[j+1].getValue() != _temp_hand[j].getValue()+1){
          if(_temp_hand[j-3].getValue() == 2){ // if the first Card in a potential Straight Flush is 2, then find an Ace with the same suit as the last hope
            if(count == 0){ // ensures only one Ace gets appended into _hand
              for(int k = 0; k < _temp_hand.size(); k++){
                if(_temp_hand[k].getValue() == 14 && _temp_hand[k].getSuit() == suit_set[i]){ // there is an Ace with the same suit
                   _temp_hand[k].switch_ace(); //
                   Card temp = _temp_hand[k];
                   _hand.push_back(temp);
                   position = j-2;
                   count++;
                   suit_counter++;
                }
              }
            }
          }
        }
      }
    }

    // for the reason suit_counter counts only to 4 (instead of 5), please refer to the top if statement
    if(suit_counter == 4){
      straight_flush = true;
      if(_hand.size() == 0){
        for (int p = position; p <position+5; p++){ // pushes the straight flush to the back of the container
          Card temp = _temp_hand[p];
          _hand.push_back(temp);
        }
      }
      else if(_hand.size() == 1 && _hand[0].getValue() == 1){ // there is already an Ace(that has been switched) in there
        for (int q = position; q <position+4; q++){ // pushes the straight flush to the back of the container
          Card temp = _temp_hand[q];
          _hand.push_back(temp);
        }
      }
      // hand.erase(hand.begin(),hand.end()-5); // erase the rest of the container, leaving only the straigth flush in the back
      // std::sort(hand.begin(),hand.end());

    }

  }

  // for the reason suit_counter counts only to 4 (instead of 5), please refer to the top if statement
  if(suit_counter != 4){ // not a flush
    straight_flush = false;
  }

}

void Hand::ace_check(){
  for(int j = 0; j < _temp_hand.size(); j++){
    if(_temp_hand[j].getValue() == 1){ // in the High Card case, if this is an Ace, switch to high ace
      _temp_hand[j].switch_ace();
    }
  }
}

int Hand::s_evaluate(){ // sorts and prints out the sorted Hand

  std::vector<Card>::iterator sort_iter; // create a sorting iterator
  std::vector<Card> temp_pair;
  int score = 0;
  int position = 0;

  // sorts _temp_hand in ascending order for easier evaluation
  std::sort(_temp_hand.begin(),_temp_hand.end());

  // prints the sorted hand
  // for (sort_iter = _temp_hand.begin();sort_iter != _temp_hand.end(); sort_iter++){ // testing purposes
  //
  //   Card temp = *sort_iter;
  //
  //   temp.show_card();
  //
  // }
  //
  // std::cout << "" << std::endl;

  //Evaluation of Card Rank begins here

  //Checks for Straight Flush
  straight_flush_check();

  //Checks for Flush
  flush_check();

  for(int i = 0; i < _temp_hand.size(); i++){

    // Check for High Card, 1-Pair, 2-Pairs, Three of a Kind, Four of a Kind,
    if(i+1 < _temp_hand.size() && _temp_hand[i].getValue() == _temp_hand[i+1].getValue()){ // is current Card object value same as next Card object value?
      // first condition of i+n < hand.size(), where n is 1,2,3, is to make sure the pointer doesnt exceed the size of the container and hence prevent segmentation fault
      if (i+2 < _temp_hand.size() && _temp_hand[i].getValue() == _temp_hand[i+2].getValue()){ // is current Card object value same as next next Card object value?
        if(i+3 < _temp_hand.size() && _temp_hand[i].getValue() == _temp_hand[i+3].getValue()){ // is current Card object value same as next next NEXT Card object value?
          four_kind = true; // it's a Four of a Kind
          position = i;
          for(position; position < i+4; position++){
            Card temp = _temp_hand[position];
            _hand.push_back(temp);
          }

        }

        else if (i+3 < _temp_hand.size() && _temp_hand[i].getValue() != _temp_hand[i+3].getValue()){ // it's a Three of a Kind
          three_kind = true;
          position = i;
          for(position; position < i+3; position++){
            Card temp = _temp_hand[position];
            _hand.push_back(temp);
          }

        }
        //if the Three Kind is located at the end of the container, confirmed no fourth pair
        else if(i+3 == _temp_hand.size()){
          three_kind = true;
          position = i;
          for(position; position < i+3; position++){
            Card temp = _temp_hand[position];
            _hand.push_back(temp);
          }
        }

      }

      else if(i>0 && _temp_hand[i-1].getValue() != _temp_hand[i].getValue()){ // extra condition to ensure that this is only a Pair IFF it is not equal to the value before it

        //push back for later:
        // pushes back the two cards that makes 1-Pair
        // _pair.push_back(hand[i]);
        // _pair.push_back(hand[i+1]);
        pair +=1;
        position = i;
        for(position; position < i+2; position++){

          Card temp = _temp_hand[position];
          // append Pair Card objects temporarily into temp_pair in case the possibility of Full House
          // if Full House is not available, append temp_pair Card objects into _hand for 1-Pair 2-Pair
          temp_pair.push_back(temp);
          std::sort(temp_pair.begin(),temp_pair.end()); // ensures that it is always in ascending order
          // _hand.push_back(temp);
        }
        // save the erasing and sorting for when it is determined whether or not it is 1-Par or 2-Pairs

        // if (pair >2){ // if there are more
        //   three_kind = true;
        //   pair = 0
        // }

      }

      else if(i ==0){ // it is definitely a Pair
        if(!straight || !straight_flush || !flush || !four_kind){
          pair +=1;
          position = i;

          for(position; position < i+2; position++){
            // std::cout << "Checkpoint 2.1" << std::endl;
            Card temp = _temp_hand[position];
            // append Pair Card objects temporarily into temp_pair in case the possibility of Full House
            // if Full House is not available, append temp_pair Card objects into _hand for 1-Pair 2-Pair
            temp_pair.push_back(temp);
            std::sort(temp_pair.begin(),temp_pair.end()); // ensures that it is always in ascending order
            // _hand.push_back(temp);
          }
        }
      }
    }
    // Check for Straight
    else if(_temp_hand[i+1].getValue() == _temp_hand[i].getValue()+1){ //is the next Card object one value higher than the current Card object?
      if(_temp_hand[i+2].getValue() == _temp_hand[i].getValue()+2){//is the next Card object two value higher than the current Card object?
        if(_temp_hand[i+3].getValue() == _temp_hand[i].getValue()+3){ //is the next Card object three value higher than the current Card object?
          if (_temp_hand[i+4].getValue() == _temp_hand[i].getValue()+4){
            straight = true;// it's a straight
            position = i;

            // if(_temp_hand[i].getValue() == 2){ // if the start of the Straight is a 2, see if there is an Ace in the _temp_hand as well
            //   int count = 0; //ensures that if there are two Ace Card objects, take one and leave for loop
            //   for(int j = 0; j < _temp_hand.size(); j++){
            //     if(count == 0){
            //       if(_temp_hand[j].getValue()== 14){ // switch Ace value from 14 to 1
            //         _temp_hand[j].switch_ace();
            //         Card temp = _temp_hand[j];
            //         _hand.push_back(temp);
            //         count ++; // this ensures that once an Ace has been appended into _hand, take no more and fill it with the rest of the sequence
            //       }
            //     }
            //
            //   }
            //   for(position; position < i+4; position ++){
            //     Card temp = _temp_hand[position];
            //     _hand.push_back(temp);
            //   }
            // }
            //
            // else{ // if the start of the Straight is NOT of value 2, append as normal
            //   for (position; position < i+5; position ++){
            //     Card temp = _temp_hand[position];
            //     _hand.push_back(temp);
            //   }
            // }
            for (position; position < i+5; position ++){ // append the straight Card objects to _hand
                Card temp = _temp_hand[position];
                _hand.push_back(temp);
              }

          }

          else if(_temp_hand[i+4].getValue() != _temp_hand[i].getValue()+4 && _temp_hand[i].getValue()==2 ){ // one last hope: is there an Ace in the _temp_hand?
            int count = 0; //ensures that if there are two Ace Card objects, take one and leave for loop
            for(int j = 0; j < _temp_hand.size(); j++){
              if(count == 0){
                if(_temp_hand[j].getValue()== 14){ // switch Ace value from 14 to 1
                  _temp_hand[j].switch_ace();
                  Card temp = _temp_hand[j];
                  _hand.push_back(temp);
                  count ++; // this ensures that once an Ace has been appended into _hand, take no more and fill it with the rest of the sequence
                  straight = true;
                  position = i;
                }
              }
            }
            if(straight){
              for(position; position < i+4; position ++){
                Card temp = _temp_hand[position];
                _hand.push_back(temp);
            }

            }
          }
        }
      }
    }

    // else{ //it may be a high card
    //
    //   if(_pair.size() == 0){ // only consider High Cards if no Pair is present
    //     _high_card.push_back(hand[i]); //push back the Card objects that could potentially be the high cards
    //   }
    //
    // }

    // std::cout << hand[i].getValue() << " "<< std::flush;
  }

  // std::cout << "" << std::endl;

  //assigning score to each possible Hand
  if(straight_flush){
    score = 9;
  }

  else if(four_kind){
    // first remove the Card objects in _temp_hand that are equivalent to those in _hand at the moment
    for(int i =0; i < _temp_hand.size(); i++){

      if (_temp_hand[i].getValue() == _hand[0].getValue()){ // if the Card object in _temp_hand is same as the Card object in _hand
        _temp_hand.erase(_temp_hand.begin()+i); // erase the duplicate Card object in _temp_hand
        i--;
      }
    }

    // append the highest kickers for Three of a Kind
    Card temp = _temp_hand.back();
    _hand.push_back(temp);
    _temp_hand.pop_back();

    score = 8;
  }

  else if(pair >= 1 && three_kind){ //full house
    if (pair >1){ // there is already a 2-Pair in place
      // std::sort(_hand.begin(),_hand.end());
      // _hand.erase(_hand.begin(),_hand.begin()+1); // this removes the first two (smallest-valued) Pair to make room for Full House
      // std::cout << "Entering while" << std::endl;
      //reduce the size of temp_pair to two, holding the two Pair
      while(temp_pair.size() != 2){
        temp_pair.erase(temp_pair.begin(),temp_pair.begin()+2);
      }
      // std::cout << "Exited while" << std::endl; // //test not needed in simulation
    }

    // push back the highest Pair to complete a full house
    //now pair will be at the end of the container, positioned 4th and 5th Card object in _hold
    for (int y= 0; y < temp_pair.size(); y++){
      Card pair_card = temp_pair[y];
      _hand.push_back(pair_card);
    }
    score = 7;
  }

  else if(flush){
    score = 6;
  }

  else if(straight){

    //if the sequence is longer than 5, the program will pick every possible 5-Card sequence and append it to _hand
    // remove the first n elements as they will be of the lowest values
    if(_hand.size() > 5){
      int cut_off = _hand.size() - 5;
      _hand.erase(_hand.begin(),_hand.begin()+cut_off);
    }
    score = 5;
  }

  else if(three_kind){
    // first remove the Card objects in _temp_hand that are equivalent to those in _hand at the moment
    for(int i =0; i < _temp_hand.size(); i++){

      if (_temp_hand[i].getValue() == _hand[0].getValue()){ // if the Card object in _temp_hand is same as the Card object in _hand
        _temp_hand.erase(_temp_hand.begin()+i); // erase the duplicate Card object in _temp_hand
        i--;
      }
    }

    // append two of the highest kickers for Three of a Kind
    for (int i = 0; i <2; i ++){
      Card temp = _temp_hand.back();
      _hand.push_back(temp);
      _temp_hand.pop_back();
    }
    std::sort(_hand.begin()+3,_hand.end());

    score = 4;
  }

  else if(pair >= 2){ // 2-Pairs
    if(pair ==2){ // 2-Pairs case

      // appends Card objects from temp_pair into _hand
      for (int y= 0; y < temp_pair.size(); y++){
        Card pair_card = temp_pair[y];
        _hand.push_back(pair_card);
      }

      //first, remove pair cards from _temp_hand
      for(int i =0; i < _temp_hand.size(); i++){

        if (_temp_hand[i].getValue() == _hand[0].getValue()){ // if the Card object in _temp_hand is same as the Card object in _hand
          _temp_hand.erase(_temp_hand.begin()+i); // erase the duplicate Card object in _temp_hand
          i--;
        }

        else if(_temp_hand[i].getValue() == _hand[2].getValue()){
          _temp_hand.erase(_temp_hand.begin()+i); // erase the duplicate Card object in _temp_hand
          i--;
        }

      }

      //now, _temp_hand is a container full of possible kicker Card object
      int p = 0;
      Card kicker = _temp_hand[p];

      for(int k = p+1; k < _temp_hand.size(); k++){
        if(kicker.getValue() < _temp_hand[k].getValue()){
          kicker = _temp_hand[k]; // switch potential kicker Card object to the new card

        }
      }
      _hand.push_back(kicker);
    }

    else if(pair >2){

      // appends Card objects from temp_pair into _hand
      for (int y= 0; y < temp_pair.size(); y++){
        Card pair_card = temp_pair[y];
        _hand.push_back(pair_card);
      }

      //remove lowest value pair first, then consider the kicker card
      std::sort(_hand.begin(),_hand.end());
      // remove the first Pair because they will have the lowest value
      _hand.erase(_hand.begin(),_hand.begin()+2); // +2 because erase does not include the +i'th element
      for(int i =0; i < _temp_hand.size(); i++){
        // erase the duplicate Card object in _temp_hand
        if (_temp_hand[i].getValue() == _hand[0].getValue()){ // if the Card object in _temp_hand is same as the Card object in _hand
          _temp_hand.erase(_temp_hand.begin()+i);
          i--;
        }

        else if(_temp_hand[i].getValue() == _hand[2].getValue()){
          _temp_hand.erase(_temp_hand.begin()+i); // erase the duplicate Card object in _temp_hand
          i--;
        }

      }

      //now, _temp_hand is a container full of possible kicker Card object
      // int p = 0;
      // std::sort(_temp_hand.begin(), _temp_hand.end());
      Card kicker = *_temp_hand.rbegin(); // let kicker be the last Card object (also the one with the highest value) from the _temp_hand

      // for(int k = p+1; k < _temp_hand.size(); k++){
      //   if(kicker.getValue() < _temp_hand[k].getValue()){
      //     kicker = _temp_hand[k]; // switch potential kicker Card object to the new card
      //
      //   }
      // }
      _hand.push_back(kicker);
    }
    score = 3;
  }

  else if(pair == 1){ // 1-Pair

    // appends Card objects from temp_pair into _hand
    for (int y= 0; y < temp_pair.size(); y++){
      Card pair_card = temp_pair[y];
      _hand.push_back(pair_card);
    }

    //first, remove pair cards from _temp_hand
    for(int i =0; i < _temp_hand.size(); i++){

      if (_temp_hand[i].getValue() == _hand[0].getValue()){ // if the Card object in _temp_hand is same as the Card object in _hand
        _temp_hand.erase(_temp_hand.begin()+i); // erase the duplicate Card object in _temp_hand
        i--;
      }
    }

    for (int j = 0; j <3; j++){
      Card temp = _temp_hand.back();
      _hand.push_back(temp);
      _temp_hand.pop_back();

    }
    std::sort(_hand.begin()+2,_hand.end());

    score = 2;
  }

  else if(pair == 0){ // high card

    for (int i = 0; i <5 ; i++){ // give the Player object 5 high cards such that Player object can compare to other Player objects more than once to determine a winner amongst two high card hands
      Card temp = _temp_hand.back();
      _hand.push_back(temp);
      _temp_hand.pop_back();
    }
    std::sort(_hand.begin(),_hand.end()); // this ensures that the High Card is always at the end of the container
    score = 1;
  }

  // _temp_hand.clear();

  return score;
}
