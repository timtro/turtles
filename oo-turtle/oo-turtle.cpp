// A very straightforwardly implemented object-ortiented turtle. The OOTurtle
// object holds turtle state, and the client interacts with the turtle through
// the interface.

#include "OOTurtle.hpp"

#include <iostream>
#include <sstream>

#include <catch2/catch.hpp>

#include "../include/test_fixtures.hpp"

using test_fixtures::delta;
using test_fixtures::manualLog;

TEST_CASE(
    "A turtle object's state should be roughly invariant when mapped "
    "around a closed contour, and the log should contain an expected "
    "string. Exceptions are not caught.") {
  std::ostringstream log;  // Log written into a stringstream.
  OOTurtle turtle(log);

  auto initial = turtle;

  turtle.move(10_m);
  turtle.turn(120_deg);
  turtle.move(10_m);
  turtle.turn(120_deg);
  turtle.move(10_m);
  turtle.turn(120_deg);

  // NB: Couldn't write these tests without writing getters.
  REQUIRE(turtle.get_x() == Approx(initial.get_x()).margin(delta));
  REQUIRE(turtle.get_y() == Approx(initial.get_y()).margin(delta));
  REQUIRE(turtle.get_th() == Approx(initial.get_th()).margin(delta));
  REQUIRE(log.str() == manualLog);
}

TEST_CASE(
    "A turtle object's state should be roughly invariant when mapped "
    "around a closed contour, and the log should contain an expected "
    "string. Exceptions are caught.") {
  std::ostringstream log;  // Log written into a stringstream.
  OOTurtle turtle(log);

  auto initial = turtle;

  try {
    turtle.move(10_m);
  } catch (MovingError) {
    std::cout << "Moving error\n";
    // + More complex logic with more try/catch?
  }
  try {
    turtle.turn(120_deg);
  } catch (TurningError) {
    std::cout << "Moving error\n";
    // + More complex logic with more try/catch?
  }
  try {
    turtle.move(10_m);
  } catch (MovingError) {
    std::cout << "Moving error\n";
    // + More complex logic with more try/catch?
  }
  try {
    turtle.turn(120_deg);
  } catch (TurningError) {
    std::cout << "Moving error\n";
    // + More complex logic with more try/catch?
  }
  try {
    turtle.move(10_m);
  } catch (MovingError) {
    std::cout << "Moving error\n";
    // + More complex logic with more try/catch?
  }
  try {
    turtle.turn(120_deg);
  } catch (TurningError) {
    std::cout << "Moving error\n";
    // + More complex logic with more try/catch?
  }

  // NB: Couldn't write these tests without writing getters.
  REQUIRE(turtle.get_x() == Approx(initial.get_x()).margin(delta));
  REQUIRE(turtle.get_y() == Approx(initial.get_y()).margin(delta));
  REQUIRE(turtle.get_th() == Approx(initial.get_th()).margin(delta));
  REQUIRE(log.str() == manualLog);
}
