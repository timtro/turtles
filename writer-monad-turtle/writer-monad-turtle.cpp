#include "../include/tfunc/function-operations.hpp"
#include "turtle.hpp"

#include <catch/catch.hpp>
#include <iostream>

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

  // std::cout << final.second;

  REQUIRE(final.first.x == Approx(initial.x).margin(delta));
  REQUIRE(final.first.y == Approx(initial.y).margin(delta));
  REQUIRE(final.first.th == Approx(initial.th).margin(delta));
  REQUIRE(final.second == std::string{manualLog});
}
