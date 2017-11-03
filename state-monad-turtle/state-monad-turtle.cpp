#include "../include/tfunc/function-operations.hpp"
#include "Pose.hpp"

#include <catch/catch.hpp>
#include <iostream>

constexpr auto delta = std::numeric_limits<double>::epsilon() * 100;


TEST_CASE("Equilateral triangle movement should leave invariant Pose, using "
          "the state-monad composition and 'do' notation") {

  Pose initial{0, 0, degree_t{0}};

  // mmove : double → Pose → (double, Pose)
  auto mmove = tf::curry(::move);
  // mturn : degree_t → Pose → (degree_t, Pose)
  auto mturn = tf::curry(::turn);
  // When curried with the first parameter, the result is in the state monad.
  // For example, mmove(10) : Pose → (double, Pose) = State<Pose, double>

  // clang-format off
  auto triangle = mdo(
    mmove(10),
    mturn(degree_t{120}),
    mmove(10),
    mturn(degree_t{120}),
    mmove(10),
    mturn(degree_t{120})
  );
  // clang-format on

  auto [a, final] = triangle(initial);
  REQUIRE(final.x == Approx(initial.x).margin(delta));
  REQUIRE(final.y == Approx(initial.y).margin(delta));
  REQUIRE(final.th == Approx(initial.th).margin(delta));
}