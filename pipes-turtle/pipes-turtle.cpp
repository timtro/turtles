#include "../include/test_fixtures.hpp"
#include "../include/tfunc/function-operations.hpp"

// Not using ../include/Pose.hpp because we need
#include "Pose-with-turtle.hpp"

#include <catch/catch.hpp>

using test_fixtures::delta;

TEST_CASE("Starting from some initial position…") {

  const Pose initial{0_m, 0_m, 0_deg};

  SECTION("… a pose should be roughly invariant when mapped around a closed "
          "contour. Here we use the crude function interface with intermediate "
          "variables") {

    const auto s1 = move(10_m, initial);
    const auto s2 = turn(120_deg, s1);
    const auto s3 = move(10_m, s2);
    const auto s4 = turn(120_deg, s3);
    const auto s5 = move(10_m, s4);
    const auto final = turn(120_deg, s5);

    REQUIRE(final.x == Approx(initial.x).margin(delta));
    REQUIRE(final.y == Approx(initial.y).margin(delta));
    REQUIRE(final.th == Approx(initial.th).margin(delta));
  }

  SECTION("… a pose should be roughly invariant when mapped around a closed "
          "contour. Here we use the crude function interface with nesting") {
    // clang-format off
    const auto final = turn(120_deg,
                          move(10_m,
                          turn(120_deg,
                          move(10_m,
                          turn(120_deg,
                          move(10_m,
                          initial  ))))));
    // clang-format on
    REQUIRE(final.x == Approx(initial.x).margin(delta));
    REQUIRE(final.y == Approx(initial.y).margin(delta));
    REQUIRE(final.th == Approx(initial.th).margin(delta));
  }

  SECTION("… a pose should be roughly invariant when mapped around a closed "
          "contour. Here we use dot-style piping. (requires turtle methods in "
          "Pose)") {

    const auto final = move(10_m, initial)
                           .turn(120_deg)
                           .move(10_m)
                           .turn(120_deg)
                           .move(10_m)
                           .turn(120_deg);

    REQUIRE(final.x == Approx(initial.x).margin(delta));
    REQUIRE(final.y == Approx(initial.y).margin(delta));
    REQUIRE(final.th == Approx(initial.th).margin(delta));
  }

  // cmove : meter_t → Pose → Pose
  const auto cmove = tf::curry(::move);
  // cturn : degree_t → Pose → Pose
  const auto cturn = tf::curry(::turn);

  SECTION("… a pose should be roughly invariant when mapped around a closed "
          "contour. Here we use an approximately point-free style") {

    // clang-format off
    const auto triangle = tf::compose(cmove(10_m),
                                      cturn(120_deg),
                                      cmove(10_m),
                                      cturn(120_deg),
                                      cmove(10_m),
                                      cturn(120_deg));
    
    const auto final = triangle(initial);
    // clang-format on

    REQUIRE(final.x == Approx(initial.x).margin(delta));
    REQUIRE(final.y == Approx(initial.y).margin(delta));
    REQUIRE(final.th == Approx(initial.th).margin(delta));
  }

  SECTION("… a pose should be roughly invariant when mapped around a closed "
          "contour. Here we use curried functions and the pipe function "
          "template.") {

    // clang-format off
    const auto final = tf::pipe(initial,
                                cmove(10_m),
                                cturn(120_deg),
                                cmove(10_m),
                                cturn(120_deg),
                                cmove(10_m),
                                cturn(120_deg));
    // clang-format on

    REQUIRE(final.x == Approx(initial.x).margin(delta));
    REQUIRE(final.y == Approx(initial.y).margin(delta));
    REQUIRE(final.th == Approx(initial.th).margin(delta));
  }
}