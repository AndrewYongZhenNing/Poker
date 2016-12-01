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

    _hand.push_back(*_temp_iter); //dereferencing _temp_iter will give one of the two cards in the Player's pockets where the pointer is pointing at

  }

  //fill _hand container with board's community cards
  for (_temp_iter = board.begin();_temp_iter != board.end(); _temp_iter++){

    _hand.push_back(*_temp_iter); // dereferencing _temp_iter will give one of the community cards in the board at game

  }

  std::cout << "\nThe hand is for " << player.show_name() << " is: " << std::endl;

  // print the Hand to check
  for (_temp_iter = _hand.begin();_temp_iter != _hand.end(); _temp_iter++){ // testing purposes

    Card temp = *_temp_iter;

    temp.show_card();

  }

  std::cout << "" << std::endl;

  //sorts and give the Hand object a score
  player.assign_score(evaluate(_hand)); // assigns the score to the Player object this Hand is for
  player.show_score(); //a method to check if the scores are evaluated properly
  player.get_score();

}

Hand::~Hand(){};

int Hand::evaluate(std::vector<Card> &hand){ // sorts and prints out the sorted Hand

  std::cout << "Evaluate the points of the player" << std::endl;

  std::vector<Card>::iterator sort_iter; // create a sorting iterator
  int score = 0;
  int start = 0;

  std::cout << "Sorting begins..." << std::endl;
  std::sort(hand.begin(),hand.end());

  // prints the sorted hand
  for (sort_iter = hand.begin();sort_iter != hand.end(); sort_iter++){ // testing purposes

    Card temp = *sort_iter;

    temp.show_card();

  }

  std::cout << "" << std::endl;

  //Evaluation of Card Rank begins here

  //Checks for Straight Flush
  straight_flush_check(hand);

  //Checks for Flush
  flush_check(hand);

  for(int i = 0; i < hand.size(); i++){

    // Check for High Card, 1-Pair, 2-Pairs, Three of a Kind, Four of a Kind,
    if(i+1 < hand.size() && hand[i].getValue() == hand[i+1].getValue()){ // is current Card object value same as next Card object value?
      // first condition of i+n < hand.size(), where n is 1,2,3, is to make sure the pointer doesnt exceed the size of the container and hence prevent segmentation fault
      if (i+2 < hand.size() && hand[i].getValue() == hand[i+2].getValue()){ // is current Card object value same as next next Card object value?
        if(i+3 < hand.size() && hand[i].getValue() == hand[i+3].getValue()){ // is current Card object value same as next next NEXT Card object value?
          four_kind = true; // it's a Four of a Kind
          // for(i; i < i+4; i++){
          //   Card temp = hand[i];
          //   hand.push_back(temp);
          // }
          // hand.erase(hand.begin(),hand.end()-4);
          // std::sort(hand.begin(),hand.end());

        }

        else if (i+3 < hand.size() && hand[i].getValue() != hand[i+3].getValue()){ // it's a Three of a Kind
          three_kind = true;
          // for(i; i < i+3; i++){
          //   Card temp = hand[i];
          //   hand.push_back(temp);
          // }
          // hand.erase(hand.begin(),hand.end()-3);
          // std::sort(hand.begin(),hand.end());
        }

      }

      else if(i>0 && hand[i-1].getValue() != hand[i].getValue()){ // extra condition to ensure that this is only a 1-Pair IFF it is not equal to the value before it

        //push back for later:
        // pushes back the two cards that makes 1-Pair
        // _pair.push_back(hand[i]);
        // _pair.push_back(hand[i+1]);
        pair +=1;
        //
        for(i; i < i+2; i++){
          Card temp = hand[i];
          hand.push_back(temp);
        }
        // save the erasing and sorting for when it is determined whether or not it is 1-Par or 2-Pairs

        // if (pair >2){ // if there are more
        //   three_kind = true;
        //   pair = 0
        // }

      }

      else if(i ==0){ // it is definitely a 1-Pair
        pair +=1;

        for(i; i < i+2; i++){
          Card temp = hand[i];
          hand.push_back(temp);
        }

      }
    }
    // Check for Straight, Full House
    else if(hand[i+1].getValue() == hand[i].getValue()+1){ //is the next Card object one value higher than the current Card object?
      if(hand[i+2].getValue() == hand[i].getValue()+2){//is the next Card object two value higher than the current Card object?
        if(hand[i+3].getValue() == hand[i].getValue()+3){ //is the next Card object three value higher than the current Card object?
          if (hand[i+4].getValue() == hand[i].getValue()+4){
            straight = true;// it's a Flush
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
    score = 8;
  }

  else if(pair == 1 && three_kind){ //full house
    score = 7;
  }

  else if(flush){
    score = 6;
  }

  else if(straight){
    score = 5;
  }

  else if(three_kind){
    score = 4;
  }

  else if(pair >= 2){ // 2-Pairs // THIS IS TEMPORARY SOLUTION; in Texas Hold'em there is no more than 2 pairs since maximum hand size is 5, will do value comparison later on
    // hand.erase(hand.begin(),hand.end()-5);
    // std::sort(hand.begin(),hand.end());
    score = 3;
  }

  else if(pair == 1){ // 1-Pair
    // hand.erase(hand.begin(),hand.end()-2);
    // std::sort(hand.begin(),hand.end());
    score = 2;
  }

  else if(pair == 0){ // high card
    score = 1;
  }

  return score;
}

void Hand::flush_check(std::vector<Card> hand){

  char suit_set[4] = {'H', 'C', 'S', 'D'};
  int suit_counter=0; // create a counter to use for each suit
  int start = 0; // create a variable to track the starting position of the flush in the hand

  for(int i = 0; i < 4; i++){ // for every suit

    for (int j = 0; j < hand.size(); j++){ // for every Card object in the container
      Card temp = hand[j];
      if(temp.getSuit() == suit_set[i]){
        // std::cout << "In flush_check, temp_suit:"<< temp.getSuit() << " suit_set: " << suit_set[i] << std::endl; // for testing purposes
        suit_counter += 1;
        if (suit_counter == 5){
          start = j-4;
        }
      }

    }

    if(suit_counter == 5){ // if found a flush, exit immediately
      flush= true;

      // for(int k = start; k < start+5; k++){
      //   Card temp = hand[k];
      //   hand.push_back(temp);
      // }
      //
      // hand.erase(hand.begin(),hand.end()-5);
      // std::sort(hand.begin(),hand.end());
      // return 0;
    }

    else{ // sets suit_counter back to zero if there are less than 5 Card objects of the current suit
      suit_counter = 0;
    }

  }

  if(suit_counter != 5){ // not a flush
    flush = false;
    // return 0;
  }

}

void Hand::straight_flush_check(std::vector<Card> hand){
  char suit_set[4] = {'H', 'C', 'S', 'D'};
  int suit_counter=0; // create a counter to use for each suit
  int start = 0;

  for(int i =0; i < 4; i++){ // check through every Suit

    for (int j = 0; j < hand.size()-1; j++){ // -1 to ensure that j+1 is still within container size (prevent segmentation fault)

      if (hand[j].getSuit() == suit_set[i] && hand[j+1].getSuit() == hand[j].getSuit() && hand[j+1].getValue() == hand[j].getValue()+1){
        suit_counter += 1;

        // this if statement helps to determine the starting position of the straight flush
        // note suit_counter is equals to 4 (rather than 5) because the if statement above has imposed that if the first 4 elements satisfy the condition AND the 5th element is the same as the 4th, the loop would end at the 4th element, so suit_counter will only count 4
        if(suit_counter == 4){ // provided that sui_counter found 5 consecutive Card objects, let the starting position be the current position subtracted by 4
          start = j-3;
        }

      }
    }

    // for the reason suit_counter counts only to 4 (instead of 5), please refer to the top if statement
    if(suit_counter == 4){
      straight_flush = true;
      // for (int k = start; k <start+5; k++){ // pushes the straight flush to the back of the container
      //   Card temp = hand[k];
      //   hand.push_back(temp);
      //
      // }
      // hand.erase(hand.begin(),hand.end()-5); // erase the rest of the container, leaving only the straigth flush in the back
      // std::sort(hand.begin(),hand.end());

    }

  }

  // for the reason suit_counter counts only to 4 (instead of 5), please refer to the top if statement
  if(suit_counter != 4){ // not a flush
    straight_flush = false;
  }

}
