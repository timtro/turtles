#include "../include/test_fixtures.hpp"
#include "../include/tfunc/function-operations.hpp"
#include "turtle.hpp"

#include <catch/catch.hpp>
#include <iostream>

using test_fixtures::delta;
using test_fixtures::manualLog;

TEST_CASE("Starting at the origin…") {

  Pose initial{0, 0, degree_t{0}};

  // cmove : double → Pose → (double, Pose)
  auto cmove = tf::curry(::move);
  // cturn : degree_t → Pose → (degree_t, Pose)
  auto cturn = tf::curry(::turn);

  SECTION("… an equlateral triangular trajectory should leave the pose "
          "invairant, but should yield an expected log trace.") {

    // clang-format off
  auto finalWM = move(10, initial)
    | cturn(degree_t{120})
    | cmove(10)
    | cturn(degree_t{120})
    | cmove(10)
    | cturn(degree_t{120});
    // clang-format on

    const Pose final = std::get<Pose>(finalWM.first);

    REQUIRE(final.x == Approx(initial.x).margin(delta));
    REQUIRE(final.y == Approx(initial.y).margin(delta));
    REQUIRE(final.th == Approx(initial.th).margin(delta));
    REQUIRE(finalWM.second == std::string{manualLog});
  }

  SECTION("… when a `hitWall` error is inserted into the binding chain, the "
          "remaining calls should be short circuited, and the error code left "
          "in the result variable") {

    const std::string manualLogWithErr{
        "moving from [0, 0, 0 rad] to [10, 0, 0 rad]\n"
        "turning from [10, 0, 0 rad] to [10, 0, 2.0944 rad]\n"
        "hitWall\n"};

    auto hitTheWall = [](auto) -> WriterWith<EitherErrorOr<Pose>> {
      return {turtleError::hitWall, std::string{"hitWall\n"}};
    };

    // clang-format off
    auto finalWM = move(10, initial)
                  | cturn(degree_t{120}) | hitTheWall
                  | cmove(10)
                  | cturn(degree_t{120})
                  | cmove(10)
                  | cturn(degree_t{120});
    // clang-format on

    std::cout << finalWM.second << std::endl;

    REQUIRE(std::holds_alternative<turtleError>(finalWM.first));
    REQUIRE(std::get<turtleError>(finalWM.first) == turtleError::hitWall);
    REQUIRE(finalWM.second == std::string{manualLogWithErr});
  }
}
