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

  // mmove : double → Pose → (double, Pose)
  auto mmove = tf::curry(::move);
  // mturn : degree_t → Pose → (degree_t, Pose)
  auto mturn = tf::curry(::turn);

  // clang-format off
  auto final = move(10, initial)
    | mturn(degree_t{120})
    | mmove(10)
    | mturn(degree_t{120})
    | mmove(10)
    | mturn(degree_t{120});
  // clang-format on

  REQUIRE(final.first.x == Approx(initial.x).margin(delta));
  REQUIRE(final.first.y == Approx(initial.y).margin(delta));
  REQUIRE(final.first.th == Approx(initial.th).margin(delta));
  REQUIRE(final.second == std::string{manualLog});
}
