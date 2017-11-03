// A very straightforwardly implemented object-ortiented turtle. The OOTurtle
// object holds turtle state, and the client interacts with the turtle through
// the interface.

#include "OOTurtle.hpp"

#include <catch/catch.hpp>
#include <iostream>
#include <sstream>

constexpr auto delta = std::numeric_limits<double>::epsilon() * 100;

TEST_CASE("Equilateral triangle movement should leave invariant Pose, using "
          "crude function interface") {

  std::ostringstream oss; // Log written into a stringstream.
  OOTurtle turtle(oss);

  auto initial = turtle;

  const double r = 10;
  turtle.move(r);
  turtle.turn(degree_t{120});
  turtle.move(r);
  turtle.turn(degree_t{120});
  turtle.move(r);
  turtle.turn(degree_t{120});

  std::cout << oss.str();

  // NB: Couldn't write these tests without writing getters.
  REQUIRE(turtle.get_x() == Approx(initial.get_x()).margin(delta));
  REQUIRE(turtle.get_y() == Approx(initial.get_y()).margin(delta));
  REQUIRE(turtle.get_th() == Approx(initial.get_th()).margin(delta));
}
