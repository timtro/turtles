#include "../include/test_fixtures.hpp"
#include "../include/tfunc/function-operations.hpp"
#include "turtle.hpp"

#include <catch/catch.hpp>
#include <iostream>

using test_fixtures::delta;
using test_fixtures::manualLog;

struct ComparatorWithReference {
  const EitherErrorOr<Pose> reference;

  // Case: we've visited upon a Pose type:
  void operator()(const Pose p) {
    // Fail if we got a Pose value while expecting an error:
    REQUIRE_FALSE(std::holds_alternative<turtleError>(reference));
    const Pose referencePose = std::get<Pose>(reference);
    REQUIRE(p.x == Approx(referencePose.x).margin(delta));
    REQUIRE(p.y == Approx(referencePose.y).margin(delta));
    REQUIRE(p.th == Approx(referencePose.th).margin(delta));
  }

  // Case: we've visited upon a turtleError type:
  void operator()(const turtleError err) {
    // Fail if we got a turtleError value while expecting a Pose:
    REQUIRE_FALSE(std::holds_alternative<Pose>(reference));
    REQUIRE(err == std::get<turtleError>(reference));
  }
};

TEST_CASE("Starting at the origin…") {

  Pose initial{0_m, 0_m, 0_deg};

  // cmove : double → Pose → (double, Pose)
  const auto cmove = tf::curry(::move);
  // cturn : degree_t → Pose → (degree_t, Pose)
  const auto cturn = tf::curry(::turn);

  SECTION("… an equlateral triangular trajectory should leave the pose "
          "invairant, but should yield an expected log trace.") {

    // clang-format off
    auto writerEitherfinal = move(10_m, initial)
                            | cturn(120_deg)
                            | cmove(10_m)
                            | cturn(120_deg)
                            | cmove(10_m)
                            | cturn(120_deg);
    // clang-format on

    std::visit(ComparatorWithReference{initial}, writerEitherfinal.first);
    REQUIRE(writerEitherfinal.second == std::string{manualLog});
  }

  SECTION("… when a `hitWall` error is inserted into the binding chain, the "
          "remaining calls should be short circuited, and the error code left "
          "in the result variable") {

    const std::string manualLogWithErr{
      "moving from [0 m, 0 m, 0 rad] to [10 m, 0 m, 0 rad]\n"
      "turning from [10 m, 0 m, 0 rad] to [10 m, 0 m, 2.0944 rad]\n"
      "hitWall\n"};

    auto hitTheWall = [](auto) -> WriterWith<EitherErrorOr<Pose>> {
      return {turtleError::hitWall, std::string{"hitWall\n"}};
    };

    // clang-format off
    auto writerEitherfinal = move(10_m, initial)
                            | cturn(120_deg) | hitTheWall
                            | cmove(10_m)
                            | cturn(120_deg)
                            | cmove(10_m)
                            | cturn(120_deg);
    // clang-format on

    std::visit(ComparatorWithReference{turtleError::hitWall},
               writerEitherfinal.first);
    REQUIRE(writerEitherfinal.second == std::string{manualLogWithErr});
  }
}
