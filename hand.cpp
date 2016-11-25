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
  player.get_score();

}

Hand::~Hand(){};

int Hand::evaluate(std::vector<Card> hand){ // sorts and prints out the sorted Hand

  std::cout << "Evaluate the points of the player" << std::endl;

  std::vector<Card>::iterator sort_iter; // create a sorting iterator
  int score = 0;

  std::cout << "Sorting begins..." << std::endl;
  std::sort(hand.begin(),hand.end());

  // prints the sorted hand
  for (sort_iter = hand.begin();sort_iter != hand.end(); sort_iter++){ // testing purposes

    Card temp = *sort_iter;

    temp.show_card();

  }

  std::cout << "" << std::endl;

  //Evaluation of Card Rank begins here

  //Checks for Flush
  flush_check(hand);

  for(int i = 0; i < hand.size(); i++){

    // Check for High Card, 1-Pair, 2-Pairs, Three of a Kind, Four of a Kind,
    if(i+1 < hand.size() && hand[i].getValue() == hand[i+1].getValue()){ // is current Card object value same as next Card object value?
      // first condition of i+n < hand.size(), where n is 1,2,3, is to make sure the pointer doesnt exceed the size of the container and hence prevent segmentation fault
      if (i+2 < hand.size() && hand[i].getValue() == hand[i+2].getValue()){ // is current Card object value same as next next Card object value?
        if(i+3 < hand.size() && hand[i].getValue() == hand[i+3].getValue()){ // is current Card object value same as next next NEXT Card object value?
          four_kind = true; // it's a Four of a Kind

        }

        else{ // it's a Three of a Kind
          three_kind = true;
        }

      }

      else{ // it's a 1-Pair

        //push back for later:
        // pushes back the two cards that makes 1-Pair
        // _pair.push_back(hand[i]);
        // _pair.push_back(hand[i+1]);

        pair +=1;

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

  if(pair == 0){ // high card
    score = 1;
  }

  else if(pair == 1){ // 1-Pair
    score = 2;
  }

  else if(pair == 2){ // 2-Pairs
    score = 3;
  }

  else if(three_kind){
    score = 4;
  }

  else if(straight){
    score = 5;
  }

  else if(flush){
    score = 6;
  }

  else if(four_kind){
    score = 8;
  }

  else if(straight_flush){
    score = 9;
  }

  return score;
}

void Hand::flush_check(std::vector<Card> hand){

  char suit_set[4] = {'H', 'C', 'S', 'D'};
  int suit_counter=0; // create a counter to use for each suit

  for(int i = 0; i < 4; i++){

    for (_temp_iter = hand.begin(); _temp_iter != hand.end(); _temp_iter++){
      Card temp = *_temp_iter;
      if(temp.getSuit() == suit_set[i]){
        suit_counter += 1;
      }

    }

    if(suit_counter == 5){
      flush = true;
    }

  }

  if(suit_counter != 5){ // not a flush
    flush = false;
  }
}

void Hand::straight_flush_check(std::vector<Card> hand){
  char suit_set[4] = {'H', 'C', 'S', 'D'};
  int suit_counter=0; // create a counter to use for each suit

  for(int i =0; i < 4; i++){

    for (int j = 0; j < hand.size()-1; j++){ // -1 to ensure that j+1 is still within container size (prevent segmentation fault)

      if (hand[j].getSuit() == suit_set[i] && hand[j+1].getValue() == hand[j].getValue()+1){
        suit_counter += 1;
      }
    }

    if(suit_counter == 5){
      straight_flush = true;
    }

  }

  if(suit_counter != 5){ // not a flush
    straight_flush = false;
  }

}
