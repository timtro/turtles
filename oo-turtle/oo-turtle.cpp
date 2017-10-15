#include "OOTurtle.hpp"
#include <iostream>
#include <sstream>

int main() {

  std::ostringstream oss;
  OOTurtle turtle(oss);

  int r = 50;

  turtle.move(r);
  turtle.turn(degree_t{120});
  turtle.move(r);
  turtle.turn(degree_t{120});
  turtle.move(r);
  turtle.turn(degree_t{120});

  std::cout << oss.str();
  return 0;
}