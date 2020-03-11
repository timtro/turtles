#include "turtle.hpp"

#include <iostream>

#include <catch2/catch.hpp>

#include "../include/test_fixtures.hpp"
#include "../tfunc/include/function-operations.hpp"

using test_fixtures::delta;

TEST_CASE(
    "This series uses composition of curried functions which return "
    "optional values. Composition is done with >>= style binding which "
    "unpacks the optional value and passes it to the next function, or "
    "fast-forwards to the end of the composition if a sentinal is return "
    "at any point in the chain. Starting from some initial position…") {
  Pose initial{0_m, 0_m, 0_deg};

  // cmove : meter_t → Pose → std::optional<Pose>
  const auto cmove = tf::curry(::move);
  // cturn : degree_t → Pose → std::optional<Pose>
  const auto cturn = tf::curry(::turn);

  SECTION(
      "… a pose should be roughly invariant when mapped around a closed "
      "contour. The full pipe chain is successful.") {
    // clang-format off
    auto final = move(10_m, initial)
                | cturn(120_deg)
                | cmove(10_m)
                | cturn(120_deg)
                | cmove(10_m)
                | cturn(120_deg);
    // clang-format on

    REQUIRE(final.has_value() == true);
    REQUIRE(final->x == Approx(initial.x).margin(delta));
    REQUIRE(final->y == Approx(initial.y).margin(delta));
    REQUIRE(final->th == Approx(initial.th).margin(delta));
  }

  SECTION(
      "… two motion commands are executed before a failure is injected "
      "into the composition demonstrating that a sentinal value will be "
      "forwarded through the piped (>>=) composition.") {
    Pose initial{0_m, 0_m, 0_deg};

    auto throw_error = [](auto) -> std::optional<Pose> { return {}; };

    // clang-format off
    auto final = move(10_m, initial)
                | cturn(120_deg) | throw_error
                | cmove(10_m)
                | cturn(120_deg)
                | cmove(10_m)
                | cturn(120_deg);
    // clang-format on

    REQUIRE(final.has_value() == false);
  }
}
