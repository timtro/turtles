#include "../include/test_fixtures.hpp"
#include "../include/tfunc/function-operations.hpp"
#include "turtle.hpp"

#include <catch/catch.hpp>
#include <iostream>

using test_fixtures::delta;

TEST_CASE("Equilateral triangle movement should leave invariant Pose, using "
          "optional monad and >>= style binding.") {

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

  REQUIRE(final->x == Approx(initial.x).margin(delta));
  REQUIRE(final->y == Approx(initial.y).margin(delta));
  REQUIRE(final->th == Approx(initial.th).margin(delta));
}

TEST_CASE("Inserting a null unit in the binding chain should short circuit the "
          "rest of the computation, leaving an empty optional result") {

  Pose initial{0_m, 0_m, 0_deg};

  // cmove : double → Pose → (double, Pose)
  const auto cmove = tf::curry(::move);
  // cturn : degree_t → Pose → (degree_t, Pose)
  const auto cturn = tf::curry(::turn);

  auto kill = [](auto) -> std::optional<Pose> { return {}; };

  // clang-format off
  auto final = move(10_m, initial)
              | cturn(120_deg) | kill 
              | cmove(10_m)
              | cturn(120_deg)
              | cmove(10_m)
              | cturn(120_deg);
  // clang-format on

  REQUIRE(final.has_value() == false);
}