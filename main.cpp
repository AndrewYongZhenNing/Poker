#include "poker.h"
#include <iostream>
#include <ctime>

int main(){

  srand(time(NULL));

  Deck mydeck = Deck();

  std::cout << "Here is my deck:" << std::endl;

  mydeck.show();

  std::cout << "\nShuffling now...\n" << std::endl;

  mydeck.shuffle(); // shuffle dem Card objects
  mydeck.show(); // show all the Card objects

  std::cout << "\nPopping top card to the bottom...\n" << std::endl;

  mydeck.new_top();
  mydeck.show();

  Player p1 = Player();




}
