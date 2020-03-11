#include "turtle.hpp"

#include <iostream>

#include <catch2/catch.hpp>

#include "../include/test_fixtures.hpp"
#include "../tfunc/include/function-operations.hpp"

using test_fixtures::delta;
using test_fixtures::manualLog;

TEST_CASE(
    "An equlateral triangular trajectory should leave the pose "
    "invairant, but should yield an expected log trace.") {
  Pose initial{0_m, 0_m, 0_deg};

  // cmove : double → Pose → (double, Pose)
  const auto cmove = tf::curry(::move);
  // cturn : degree_t → Pose → (degree_t, Pose)
  const auto cturn = tf::curry(::turn);

  // clang-format off
  auto final = move(10_m, initial)
    | cturn(120_deg)
    | cmove(10_m)
    | cturn(120_deg)
    | cmove(10_m)
    | cturn(120_deg);
  // clang-format on

  REQUIRE(final.first.x == Approx(initial.x).margin(delta));
  REQUIRE(final.first.y == Approx(initial.y).margin(delta));
  REQUIRE(final.first.th == Approx(initial.th).margin(delta));
  REQUIRE(final.second == std::string{manualLog});
}
