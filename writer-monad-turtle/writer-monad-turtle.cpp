#include "../include/test_fixtures.hpp"
#include "../include/tfunc/function-operations.hpp"
#include "turtle.hpp"

#include <catch/catch.hpp>
#include <iostream>

using test_fixtures::delta;
using test_fixtures::manualLog;

TEST_CASE("An equlateral triangular trajectory should leave the pose "
          "invairant, but should yield an expected log trace.") {

  Pose initial{0, 0, degree_t{0}};

  // cmove : double → Pose → (double, Pose)
  auto cmove = tf::curry(::move);
  // cturn : degree_t → Pose → (degree_t, Pose)
  auto cturn = tf::curry(::turn);

  // clang-format off
  auto final = move(10, initial)
    | cturn(degree_t{120})
    | cmove(10)
    | cturn(degree_t{120})
    | cmove(10)
    | cturn(degree_t{120});
  // clang-format on

  REQUIRE(final.first.x == Approx(initial.x).margin(delta));
  REQUIRE(final.first.y == Approx(initial.y).margin(delta));
  REQUIRE(final.first.th == Approx(initial.th).margin(delta));
  REQUIRE(final.second == std::string{manualLog});
}
