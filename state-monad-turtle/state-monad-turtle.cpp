#include "../include/test_fixtures.hpp"
#include "../include/tfunc/function-operations.hpp"
#include "turtle.hpp"

#include <catch/catch.hpp>
#include <iostream>

using test_fixtures::delta;

TEST_CASE("Using the State monad, starting at the origin and turtle should…") {

  const Pose initial{0, 0, degree_t{0}};

  // mmove : double → Pose → (double, Pose)
  auto mmove = tf::curry(::move);
  // mturn : degree_t → Pose → (degree_t, Pose)
  auto mturn = tf::curry(::turn);

  SECTION("… be Pose invariant sent on the journey of an equilateral triangle, "
          "using operator| notation.") {

    // clang-format off
    auto triangle = mmove(10)
              | [&](auto) { return mturn(degree_t{120}); } 
              | [&](auto) { return mmove(10); }
              | [&](auto) { return mturn(degree_t{120}); }
              | [&](auto) { return mmove(10); }
              | [&](auto) { return mturn(degree_t{120}); };
    // clang-format on

    // const Pose final = std::get<Pose>(eitherFinal);

    auto [a, final] = triangle(initial);

    REQUIRE(final.x == Approx(initial.x).margin(delta));
    REQUIRE(final.y == Approx(initial.y).margin(delta));
    REQUIRE(final.th == Approx(initial.th).margin(delta));
  }

  SECTION("… be Pose invariant sent on the journey of an equilateral triangle, "
          "using operator>> notation.") {

    // clang-format off
    auto triangle = mmove(10) 
              >> mturn(degree_t{120})
              >> mmove(10)
              >> mturn(degree_t{120})
              >> mmove(10)
              >> mturn(degree_t{120});
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
}