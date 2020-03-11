#include "turtle.hpp"

#include <iostream>
#include <vector>

#include <catch2/catch.hpp>

#include "../include/test_fixtures.hpp"

using test_fixtures::delta;
using test_fixtures::manualLog;
using test_fixtures::manualLogWithErr;

struct ComparatorWithReference {
  const ErrorOr<Pose> reference;

  // Case: we've visited upon a Pose type:
  void operator()(const Pose p) {
    // Fail if we got a Pose value while expecting an error:
    REQUIRE_FALSE(std::holds_alternative<turtleError>(reference));
    const Pose referencePose = std::get<Pose>(reference);
    REQUIRE(p.x == Approx(referencePose.x).margin(delta));
    REQUIRE(p.y == Approx(referencePose.y).margin(delta));
    REQUIRE(p.th == Approx(referencePose.th).margin(delta));
  }

  // Case: we've visited upon a turtleError type:
  void operator()(const turtleError err) {
    // Fail if we got a turtleError value while expecting a Pose:
    REQUIRE_FALSE(std::holds_alternative<Pose>(reference));
    REQUIRE(err == std::get<turtleError>(reference));
  }
};

TEST_CASE("Starting from some initial position…") {
  const Pose initial{0_m, 0_m, 0_deg};

  SECTION(
      "pose should be roughly invariant when mapped around a closed "
      "contour such as an equilateral triangle.") {
    std::vector<TurtleCommand> triangle{TurtleMove{10_m}, TurtleTurn{120_deg},
                                        TurtleMove{10_m}, TurtleTurn{120_deg},
                                        TurtleMove{10_m}, TurtleTurn{120_deg}};

    auto [final, log] = run_all(initial, triangle);
    std::visit(ComparatorWithReference{initial}, final);
    REQUIRE(log == manualLog);
  }

  SECTION(
      "pose should be roughly invariant when mapped around a closed "
      "contour such as an equilateral triangle.") {
    std::vector<TurtleCommand> triangle{
        TurtleMove{10_m}, TurtleTurn{120_deg}, TurtleMove{1000_m},
        //                                     WHOOPS!    ^^^^
        TurtleTurn{120_deg}, TurtleMove{10_m}, TurtleTurn{120_deg}};

    auto [final, log] = run_all(initial, triangle);
    std::visit(ComparatorWithReference{turtleError::hitWall}, final);
    REQUIRE(log == manualLogWithErr);
  }
}
