#include "turtle.hpp"

#include <iostream>

#include <catch2/catch.hpp>

#include "../include/test_fixtures.hpp"
#include "../tfunc/include/function-operations.hpp"

using test_fixtures::delta;

TEST_CASE("Using the State monad, starting at the origin and turtle should…") {
  const Pose initial{0_m, 0_m, 0_deg};

  // cmove : double → Pose → (double, Pose)
  const auto cmove = tf::curry(::move);
  // cturn : degree_t → Pose → (degree_t, Pose)
  const auto cturn = tf::curry(::turn);

  SECTION(
      "… be Pose invariant sent on the journey of an equilateral triangle, "
      "using operator| notation.") {
    // clang-format off
    auto triangle = cmove(10_m)
                  | [&](auto) { return cturn(120_deg); }
                  | [&](auto) { return cmove(10_m); }
                  | [&](auto) { return cturn(120_deg); }
                  | [&](auto) { return cmove(10_m); }
                  | [&](auto) { return cturn(120_deg); };
    // clang-format on

    // const Pose final = std::get<Pose>(eitherFinal);

    auto [a, final] = triangle(initial);

    REQUIRE(final.x == Approx(initial.x).margin(delta));
    REQUIRE(final.y == Approx(initial.y).margin(delta));
    REQUIRE(final.th == Approx(initial.th).margin(delta));
  }

  SECTION(
      "… be Pose invariant sent on the journey of an equilateral triangle, "
      "using operator>> notation.") {
    // clang-format off
    auto triangle = cmove(10_m)
              >> cturn(120_deg)
              >> cmove(10_m)
              >> cturn(120_deg)
              >> cmove(10_m)
              >> cturn(120_deg);
    // clang-format on

    // const Pose final = std::get<Pose>(eitherFinal);

    auto [a, final] = triangle(initial);

    REQUIRE(final.x == Approx(initial.x).margin(delta));
    REQUIRE(final.y == Approx(initial.y).margin(delta));
    REQUIRE(final.th == Approx(initial.th).margin(delta));
  }

  SECTION(
      "… be left apprximately invariant sent on the journey of an equilateral "
      "triangle, using \"do\" notation.") {
    // clang-format off
    auto triangle = mdo(cmove(10_m),
                        cturn(120_deg),
                        cmove(10_m),
                        cturn(120_deg),
                        cmove(10_m),
                        cturn(120_deg));
    // clang-format on

    auto [a, final] = triangle(initial);

    REQUIRE(final.x == Approx(initial.x).margin(delta));
    REQUIRE(final.y == Approx(initial.y).margin(delta));
    REQUIRE(final.th == Approx(initial.th).margin(delta));
  }
}
