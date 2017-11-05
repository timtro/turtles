// A very straightforwardly implemented object-ortiented turtle. The OOTurtle
// object holds turtle state, and the client interacts with the turtle through
// the interface.

#include "../include/test_fixtures.hpp"
#include "OOTurtle.hpp"

#include <catch/catch.hpp>
#include <iostream>
#include <sstream>

using test_fixtures::delta;
using test_fixtures::manualLog;

TEST_CASE("Equilateral triangle movement should leave invariant Pose, using "
          "turtle object to hold state and no error handling") {

  std::ostringstream log; // Log written into a stringstream.
  OOTurtle turtle(log);

  auto initial = turtle;

  turtle.move(10);
  turtle.turn(degree_t{120});
  turtle.move(10);
  turtle.turn(degree_t{120});
  turtle.move(10);
  turtle.turn(degree_t{120});

  // NB: Couldn't write these tests without writing getters.
  REQUIRE(turtle.get_x() == Approx(initial.get_x()).margin(delta));
  REQUIRE(turtle.get_y() == Approx(initial.get_y()).margin(delta));
  REQUIRE(turtle.get_th() == Approx(initial.get_th()).margin(delta));
  REQUIRE(log.str() == manualLog);
}

TEST_CASE(
    "Equilateral triangle movement should leave invariant Pose, using "
    "turtle object to hold state and try/catch blocks to handle errors.") {

  std::ostringstream log; // Log written into a stringstream.
  OOTurtle turtle(log);

  auto initial = turtle;

  try {
    turtle.move(10);
  } catch (MovingError) {
    std::cout << "Moving error\n";
  }
  try {
    turtle.turn(degree_t{120});
  } catch (TurningError) {
    std::cout << "Moving error\n";
  }
  try {
    turtle.move(10);
  } catch (MovingError) {
    std::cout << "Moving error\n";
  }
  try {
    turtle.turn(degree_t{120});
  } catch (TurningError) {
    std::cout << "Moving error\n";
  }
  try {
    turtle.move(10);
  } catch (MovingError) {
    std::cout << "Moving error\n";
  }
  try {
    turtle.turn(degree_t{120});
  } catch (TurningError) {
    std::cout << "Moving error\n";
  }

  // NB: Couldn't write these tests without writing getters.
  REQUIRE(turtle.get_x() == Approx(initial.get_x()).margin(delta));
  REQUIRE(turtle.get_y() == Approx(initial.get_y()).margin(delta));
  REQUIRE(turtle.get_th() == Approx(initial.get_th()).margin(delta));
  REQUIRE(log.str() == manualLog);
}