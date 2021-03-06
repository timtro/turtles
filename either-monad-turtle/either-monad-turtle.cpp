#include "turtle.hpp"

#include <iostream>

#include <catch2/catch.hpp>

#include "../include/test_fixtures.hpp"
#include "../tfunc/include/function-operations.hpp"

using test_fixtures::delta;

struct ComparatorWithReference {
  const ErrorOr<Pose> reference;

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

TEST_CASE("Using the Either monad, starting at the origin and turtle should…") {
  const Pose initial{0_m, 0_m, 0_deg};

  // cmove : double → Pose → (double, Pose)
  const auto cmove = tf::curry(::move);
  // cturn : degree_t → Pose → (degree_t, Pose)
  const auto cturn = tf::curry(::turn);

  SECTION(
      "Be left apprximately invariant sent on the journy of an equilateral "
      "triangle.") {
    // clang-format off
    auto eitherFinal = move(10_m, initial)
                      | cturn(120_deg)
                      | cmove(10_m)
                      | cturn(120_deg)
                      | cmove(10_m)
                      | cturn(120_deg);
    // clang-format on

    std::visit(ComparatorWithReference{initial}, eitherFinal);
  }

  SECTION(
      "When a `hitWall` error is inserted into the binding chain, the "
      "remaining calls should be short circuited, and the error code left "
      "in the result variable") {
    auto hitTheWall = [](auto) -> ErrorOr<Pose> {
      return turtleError::hitWall;
    };

    // clang-format off
    auto eitherFinal = move(10_m, initial)
                      | cturn(120_deg) | hitTheWall
                      | cmove(10_m)
                      | cturn(120_deg)
                      | cmove(10_m)
                      | cturn(120_deg);
    // clang-format on

    std::visit(ComparatorWithReference{turtleError::hitWall}, eitherFinal);
  }
}
