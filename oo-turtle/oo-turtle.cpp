// A very straightforwardly implemented object-ortiented turtle. The OOTurtle
// object holds turtle state, and the client interacts with the turtle through
// the interface.

#include "OOTurtle.hpp"

#include <catch/catch.hpp>
#include <iostream>
#include <sstream>

constexpr auto delta = std::numeric_limits<double>::epsilon() * 100;

constexpr char manualLog[] = {
    "moving from [0, 0, 0 rad] to [10, 0, 0 rad]\n"
    "turning from [10, 0, 0 rad] to [10, 0, 2.0944 rad]\n"
    "moving from [10, 0, 2.0944 rad] to [5, 8.66025, 2.0944 rad]\n"
    "turning from [5, 8.66025, 2.0944 rad] to [5, 8.66025, 4.18879 rad]\n"
    "moving from [5, 8.66025, 4.18879 rad] to [-2.66454e-15, 3.55271e-15, "
    "4.18879 rad]\n"
    "turning from [-2.66454e-15, 3.55271e-15, 4.18879 rad] to [-2.66454e-15, "
    "3.55271e-15, 0 rad]\n"};

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
  } catch (MovingError) {
    std::cout << "Moving error\n";
  }
  try {
    turtle.move(10);
  } catch (MovingError) {
    std::cout << "Moving error\n";
  }
  try {
    turtle.turn(degree_t{120});
  } catch (MovingError) {
    std::cout << "Moving error\n";
  }
  try {
    turtle.move(10);
  } catch (MovingError) {
    std::cout << "Moving error\n";
  }
  try {
    turtle.turn(degree_t{120});
  } catch (MovingError) {
    std::cout << "Moving error\n";
  }

  // NB: Couldn't write these tests without writing getters.
  REQUIRE(turtle.get_x() == Approx(initial.get_x()).margin(delta));
  REQUIRE(turtle.get_y() == Approx(initial.get_y()).margin(delta));
  REQUIRE(turtle.get_th() == Approx(initial.get_th()).margin(delta));
  REQUIRE(log.str() == manualLog);
}