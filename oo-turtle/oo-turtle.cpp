// A very straightforwardly implemented object-ortiented turtle. The OOTurtle
// object holds turtle state, and the client interacts with the turtle through
// the interface.

#include "OOTurtle.hpp"
#include <iostream>
#include <sstream>

int main() {

  std::ostringstream oss; // Log written into a stringstream.
  OOTurtle turtle(oss);

  int r = 50;

  // Equilateral triangle. Should be an invariant transformation on the state.
  turtle.move(r);
  turtle.turn(degree_t{120});
  turtle.move(r);
  turtle.turn(degree_t{120});
  turtle.move(r);
  turtle.turn(degree_t{120});

  std::cout << oss.str();
  return 0;
}