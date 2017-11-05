#include "../include/test_fixtures.hpp"
#include "../include/tfunc/function-operations.hpp"
#include "turtle.hpp"

#include <catch/catch.hpp>

using test_fixtures::delta;

TEST_CASE(
    "Using the State+Either monad, starting at the origin and turtle should…") {

  const Pose initial{0, 0, degree_t{0}};

  // cmove : double → Pose → (double, Pose)
  auto cmove = tf::curry(::move);
  // cturn : degree_t → Pose → (degree_t, Pose)
  auto cturn = tf::curry(::turn);

  SECTION("Be Pose invariant sent on the journey of an equilateral triangle, "
          "using operator| notation.") {

    // clang-format off
    auto triangle = cmove(10)
                  | [&](auto) { return cturn(degree_t{120}); } 
                  | [&](auto) { return cmove(10); }
                  | [&](auto) { return cturn(degree_t{120}); }
                  | [&](auto) { return cmove(10); }
                  | [&](auto) { return cturn(degree_t{120}); };
    // clang-format on

    // const Pose final = std::get<Pose>(eitherFinal);

    auto [a, final] = triangle(initial);

    REQUIRE(final.x == Approx(initial.x).margin(delta));
    REQUIRE(final.y == Approx(initial.y).margin(delta));
    REQUIRE(final.th == Approx(initial.th).margin(delta));
  }

  SECTION("Be Pose invariant sent on the journey of an equilateral triangle, "
          "using operator>> notation.") {

    // clang-format off
    auto triangle = cmove(10) 
                  >> cturn(degree_t{120})
                  >> cmove(10)
                  >> cturn(degree_t{120})
                  >> cmove(10)
                  >> cturn(degree_t{120});
    // clang-format on

    // const Pose final = std::get<Pose>(eitherFinal);

    auto [a, final] = triangle(initial);

    REQUIRE(final.x == Approx(initial.x).margin(delta));
    REQUIRE(final.y == Approx(initial.y).margin(delta));
    REQUIRE(final.th == Approx(initial.th).margin(delta));
  }

  SECTION(
      "Be left apprximately invariant sent on the journey of an equilateral "
      "triangle, using \"do\" notation.") {

    // clang-format off
    auto triangle = mdo(cmove(10),
                        cturn(degree_t{120}),
                        cmove(10),
                        cturn(degree_t{120}),
                        cmove(10),
                        cturn(degree_t{120}));
    // clang-format on

    auto [a, final] = triangle(initial);

    REQUIRE(final.x == Approx(initial.x).margin(delta));
    REQUIRE(final.y == Approx(initial.y).margin(delta));
    REQUIRE(final.th == Approx(initial.th).margin(delta));
  }

  SECTION("When a `hitWall` error is inserted into the binding chain, the "
          "remaining calls should be short circuited, and the error code left "
          "in the result variable") {

    auto hitTheWall = [](auto s) -> StateWith<EitherErrorOr<Pose>> {
      return {turtleError::hitWall, s};
    };

    // clang-format off
    auto triangle = cmove(10) 
                  >> cturn(degree_t{120}) >> hitTheWall
                  >> cmove(10)               
                  >> cturn(degree_t{120})
                  >> cmove(10)
                  >> cturn(degree_t{120});
    // clang-format on

    auto [a, final] = triangle(initial);

    REQUIRE(std::holds_alternative<turtleError>(a));
    REQUIRE(std::get<turtleError>(a) == turtleError::hitWall);
    REQUIRE(final.x == Approx(10));
    REQUIRE(final.y == Approx(0));
    REQUIRE(final.th == Approx(degree_t{120}));
  }
}