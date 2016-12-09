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

      _temp_hand.push_back(*_temp_iter); //dereferencing _temp_iter will give one of the two cards in the Player's pockets where the pointer is pointing at

    }

    //fill _hand container with board's community cards
    for (_temp_iter = board.begin();_temp_iter != board.end(); _temp_iter++){

      _temp_hand.push_back(*_temp_iter); // dereferencing _temp_iter will give one of the community cards in the board at game

    }

    //sorts and give the Hand object a score
    player.assign_score(s_evaluate()); // assigns the score to the Player object this Hand is for
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

  std::cout << "The sorted hand is:" << std::endl;
  // sorts _temp_hand in ascending order for easier evaluation
  std::sort(_temp_hand.begin(),_temp_hand.end());

  // prints the sorted hand
  for (sort_iter = _temp_hand.begin();sort_iter != _temp_hand.end(); sort_iter++){ // testing purposes

    Card temp = *sort_iter;

    temp.show_card();

  }

  std::cout << "" << std::endl;

  //Evaluation of Card Rank begins here

  //Checks for Straight Flush, Straight, Flush and Royal Flush
  straight_flush_check();

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

        pair +=1;
        position = i;
        for(position; position < i+2; position++){

          Card temp = _temp_hand[position];
          // append Pair Card objects temporarily into temp_pair in case the possibility of Full House
          // if Full House is not available, append temp_pair Card objects into _hand for 1-Pair 2-Pair
          temp_pair.push_back(temp);
          std::sort(temp_pair.begin(),temp_pair.end()); // ensures that it is always in ascending order
        }
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
  }

  std::cout << "" << std::endl;

  //assigning score to each possible Hand
  if(royal_flush){
    score = 10;
  }

  else if(straight_flush){
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
      //reduce the size of temp_pair to two, holding the highest valued Pair
      while(temp_pair.size() != 2){
        temp_pair.erase(temp_pair.begin(),temp_pair.begin()+2);
      }
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
      Card kicker = *_temp_hand.rbegin(); // let kicker be the last Card object (also the one with the highest value) from the _temp_hand
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

void Hand::straight_flush_check(){
  char suit_set[4] = {'H', 'C', 'S', 'D'};
  int suit_counter=0; // create a counter to use for each suit
  int position = 0;
  int count = 0;
  char flush_suit = 'n'; // initialise a dummy suit index
  std::vector<Card> flush_hand;
  std::vector<Card> straight_hand;

  //Check for flush
  for(int i = 0; i < 4; i++){ // for every suit

    for (int j = 0; j < _temp_hand.size(); j++){ // for every Card object in the container
      Card temp = _temp_hand[j];
      if(temp.getSuit() == suit_set[i]){
        suit_counter += 1;
        if (suit_counter == 5){
          flush_suit = suit_set[i]; // records the suit that forms a flush in the hand
        }
      }

    }

    if(suit_counter == 5){ // if found a flush, exit immediately
      flush= true;

      // using the recorded flush_suit, get all the highest value flush Card objects
      for(int k = 0; k < _temp_hand.size(); k++){
        Card temp = _temp_hand.rbegin()[k]; // iterate from behind to get the highest value flush
        if(temp.getSuit() == flush_suit && flush_hand.size() != 5){
          flush_hand.push_back(temp);
        }
      }
      //ensures flush cards are in ascending order
      std::sort(flush_hand.begin(),flush_hand.end());
    }

    else{ // sets suit_counter back to zero if there are less than 5 Card objects of the current suit
      suit_counter = 0;
    }
  }

  //Check for straight
  for(int i = 0; i < _temp_hand.size(); i++){
    //only enter the straight if loops if straight_flush is false
    if(!straight_flush){
      if(i+1 < _temp_hand.size() && _temp_hand[i+1].getValue() == _temp_hand[i].getValue()+1){ //is the next Card object one value higher than the current Card object?
        if(i+2 < _temp_hand.size() && _temp_hand[i+2].getValue() == _temp_hand[i].getValue()+2){//is the next Card object two value higher than the current Card object?
          if(i+3 < _temp_hand.size() && _temp_hand[i+3].getValue() == _temp_hand[i].getValue()+3){ //is the next Card object three value higher than the current Card object?
            if (i+4 < _temp_hand.size() && _temp_hand[i+4].getValue() == _temp_hand[i].getValue()+4){
              straight = true;// it's a straight
              position = i;

              //if straight_hand already has a straight in it, the program will pick the highest sequence of 5 cards to be appended into _hand
              // remove the first n elements as they will be of the lowest values
              if(straight_hand.size() > 0){
                straight_hand.clear();
              }
              //Now append latest Straight Card objects
              for (position; position < i+5; position ++){ // append the straight Card objects to _hand
                Card temp = _temp_hand[position];
                straight_hand.push_back(temp);
                std::sort(straight_hand.begin(),straight_hand.end());
              }

              //Compare with flush hand, if it is the same as flush, exit for loop
              if(flush){
                for(int z = 0; z < straight_hand.size(); z++){
                  if(straight_hand[z].getValue() == flush_hand[z].getValue() && straight_hand[z].getSuit() == flush_hand[z].getSuit()){
                    count ++;
                  }
                }
                if(count == 5){ // if all 5 Card objects in each container are equivalent
                  straight_flush = true;
                  for (int j = 0; j < straight_hand.size(); j++){
                    Card temp = straight_hand[j];
                    _hand.push_back(temp);
                  }
                  if(_hand[0].getValue() == 10 && _hand[1].getValue() == 11 && _hand[2].getValue() == 12 && _hand[3].getValue() == 13 && _hand[4].getValue() == 14){
                    royal_flush = true;
                  }
                }
              }
            }

            else if(i+4 < _temp_hand.size() && _temp_hand[i+4].getValue() != _temp_hand[i].getValue()+4 && _temp_hand[i].getValue()==2 ){ // one last hope: is there an Ace in the _temp_hand?
              int ace_count = 0; //ensures that if there are two or more Ace Card objects, take one and leave for loop
              for(int j = 0; j < _temp_hand.size(); j++){
                if(ace_count == 0){
                  if(_temp_hand[j].getValue()== 14){ // switch Ace value from 14 to 1
                    _temp_hand[j].switch_ace();
                    Card temp = _temp_hand[j];
                    straight_hand.push_back(temp);
                    ace_count ++; // this ensures that once an Ace has been appended into _hand, take no more and fill it with the rest of the sequence
                    straight = true;
                    position = i;

                    //After appending Ace, now append the remaining 4 of the Straight sequence
                    for(position; position < i+4; position ++){
                      Card temp = _temp_hand[position];
                      straight_hand.push_back(temp);
                      std::sort(straight_hand.begin(),straight_hand.end());
                    }
                    if(flush){ // if there is also a Flush, check through Straight to see if both containers match up
                      for(int z = 0; z < straight_hand.size(); z++){
                        if(straight_hand[z].getValue() == flush_hand[z].getValue() && straight_hand[z].getSuit() == flush_hand[z].getSuit()){
                          count ++;
                        }
                      }

                      if(count == 5){ // if all 5 Card objects in each container are equivalent
                        straight_flush = true;
                        for (int j = 0; j < straight_hand.size(); j++){
                          Card temp = straight_hand[j];
                          _hand.push_back(temp);
                        }
                        if(_hand[0].getValue() == 10 && _hand[1].getValue() == 11 && _hand[2].getValue() == 12 && _hand[3].getValue() == 13 && _hand[4].getValue() == 14){
                          royal_flush = true;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  count = 0; //reinitialise as 0 to be used in determining whether the hand is also straight flush
  if(straight_flush){
    if(_hand[0].getValue() == 10 && _hand[1].getValue() == 11 && _hand[2].getValue() == 12 && _hand[3].getValue() == 13 && _hand[4].getValue() == 14){
      royal_flush = true;
    }
  }

  else if(straight && !flush){ //if solely a Straight, append Card objects from straight_hand to _hand
    for(int q = 0; q < straight_hand.size(); q++){
      Card temp = straight_hand[q];
      _hand.push_back(temp);
    }
  }

  else if(flush && !straight){ // if solely a Flush, append Card objects from flush_hand to _hand
    for(int r = 0; r < flush_hand.size(); r++){
      Card temp = flush_hand[r];
      _hand.push_back(temp);
    }
  }

  else if (flush || straight){ // if both are available but not as a straight flush, append flush as it is higher
  	for (int s = 0; s < flush_hand.size(); s++){
  		Card temp = flush_hand[s];
  		_hand.push_back(temp);
  	}
  }

}

void Hand::ace_check(){
  for(int j = 0; j < _temp_hand.size(); j++){
    if(_temp_hand[j].getValue() == 1){ // in the High Card case, if this is an Ace, switch to high ace
      _temp_hand[j].switch_ace();
    }
  }
}

int Hand::s_evaluate(){ // Simular to evaluate(), but evaluates for the simulation

  std::vector<Card>::iterator sort_iter; // create a sorting iterator
  std::vector<Card> temp_pair;
  int score = 0;
  int position = 0;

  // sorts _temp_hand in ascending order for easier evaluation
  std::sort(_temp_hand.begin(),_temp_hand.end());
  //Evaluation of Card Rank begins here

  //Checks for Straight Flush
  straight_flush_check();

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

        pair +=1;
        position = i;
        for(position; position < i+2; position++){

          Card temp = _temp_hand[position];
          // append Pair Card objects temporarily into temp_pair in case the possibility of Full House
          // if Full House is not available, append temp_pair Card objects into _hand for 1-Pair 2-Pair
          temp_pair.push_back(temp);
          std::sort(temp_pair.begin(),temp_pair.end()); // ensures that it is always in ascending order
        }
        // save the erasing and sorting for when it is determined whether or not it is 1-Pair or 2-Pairs



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
  }

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
      while(temp_pair.size() != 2){
        temp_pair.erase(temp_pair.begin(),temp_pair.begin()+2);
      }
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

      Card kicker = *_temp_hand.rbegin(); // let kicker be the last Card object (also the one with the highest value) from the _temp_hand

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
