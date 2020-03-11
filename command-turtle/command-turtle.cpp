#include "turtle.hpp"

#include <catch2/catch.hpp>

#include <iostream>
#include <vector>

#include "../include/test_fixtures.hpp"
#include "../tfunc/include/function-operations.hpp"

using test_fixtures::delta;
using test_fixtures::manualLog;

TEST_CASE(
    "Pose should be roughly invariant when mapped around a closed "
    "contour such as an equilateral triangle.") {
  const Pose initial{0_m, 0_m, 0_deg};

  std::vector<TurtleCommand> triangle{TurtleMove{10_m}, TurtleTurn{120_deg},
                                      TurtleMove{10_m}, TurtleTurn{120_deg},
                                      TurtleMove{10_m}, TurtleTurn{120_deg}};

  auto final = run_all(initial, triangle);

  REQUIRE(final.x == Approx(initial.x).margin(delta));
  REQUIRE(final.y == Approx(initial.y).margin(delta));
  REQUIRE(final.th == Approx(initial.th).margin(delta));
}
