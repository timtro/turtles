#include "../include/test_fixtures.hpp"
#include "../include/tfunc/function-operations.hpp"
#include "turtle.hpp"

#include <catch/catch.hpp>
#include <iostream>

using test_fixtures::delta;

TEST_CASE("Starting from some initial position…") {

  Pose initial{0_m, 0_m, 0_deg};

  // cmove : meter_t → Pose → std::optional<Pose>
  const auto cmove = tf::curry(::move);
  // cturn : degree_t → Pose → std::optional<Pose>
  const auto cturn = tf::curry(::turn);

  SECTION("… a pose should be roughly invariant when mapped around a closed "
          "contour. This section uses composition of curried functions which "
          "return optional values, and composition is done with >>= style "
          "binding. The full pipe chain is successful.") {

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

  SECTION("… a failure is injected into the composition of commands, "
          "deonstrating that a sentinal value will be forwarded through the "
          "piped (>>=) composition.") {

    Pose initial{0_m, 0_m, 0_deg};

    auto inject_sentinal = [](auto) -> std::optional<Pose> { return {}; };

    // clang-format off
    auto final = move(10_m, initial)
                | cturn(120_deg) | inject_sentinal
                | cmove(10_m)
                | cturn(120_deg)
                | cmove(10_m)
                | cturn(120_deg);
    // clang-format on

    REQUIRE(final.has_value() == false);
  }
}