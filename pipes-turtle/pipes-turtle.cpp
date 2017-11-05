#include "../include/tfunc/function-operations.hpp"
#include "Pose.hpp"

#include <catch/catch.hpp>

constexpr auto delta = std::numeric_limits<double>::epsilon() * 100;

TEST_CASE("Equilateral triangle movement should leave invariant Pose, using…") {

  // mmove : double → Pose → (double, Pose)
  auto cmove = tf::curry(::move);
  // mturn : degree_t → Pose → (degree_t, Pose)
  auto cturn = tf::curry(::turn);

  Pose initial{0, 0, degree_t{0}};

  SECTION("… the crude function interface") {
    const auto s1 = move(10, initial);
    const auto s2 = turn(degree_t{120}, s1);
    const auto s3 = move(10, s2);
    const auto s4 = turn(degree_t{120}, s3);
    const auto s5 = move(10, s4);
    const auto final = turn(degree_t{120}, s5);

    REQUIRE(final.x == Approx(initial.x).margin(delta));
    REQUIRE(final.y == Approx(initial.y).margin(delta));
    REQUIRE(final.th == Approx(initial.th).margin(delta));
  }

  SECTION("… crude function interface with nesting") {
    // clang-format off
    const auto final = turn(degree_t{120},
                          move(10,
                          turn(degree_t{120},
                          move(10,
                          turn(degree_t{120},
                          move(10,
                          initial  ))))));
    // clang-format on
    REQUIRE(final.x == Approx(initial.x).margin(delta));
    REQUIRE(final.y == Approx(initial.y).margin(delta));
    REQUIRE(final.th == Approx(initial.th).margin(delta));
  }

  SECTION("… dot-style piping.") {

    const auto final = move(10, initial)
                           .turn(degree_t{120})
                           .move(10)
                           .turn(degree_t{120})
                           .move(10)
                           .turn(degree_t{120});

    REQUIRE(final.x == Approx(initial.x).margin(delta));
    REQUIRE(final.y == Approx(initial.y).margin(delta));
    REQUIRE(final.th == Approx(initial.th).margin(delta));
  }

  SECTION("… approximately point-free style") {

    // clang-format off
    const auto triangle = tf::compose(
                            cmove(10),
                            cturn(degree_t{120}),
                            cmove(10),
                            cturn(degree_t{120}),
                            cmove(10),
                            cturn(degree_t{120}));
    
    const auto final = triangle(initial);
    // clang-format on

    REQUIRE(final.x == Approx(initial.x).margin(delta));
    REQUIRE(final.y == Approx(initial.y).margin(delta));
    REQUIRE(final.th == Approx(initial.th).margin(delta));
  }

  SECTION("… curried functions and the pipe function template.") {

    // clang-format off
    const auto final = tf::pipe(initial,
                              cmove(10),
                              cturn(degree_t{120}),
                              cmove(10),
                              cturn(degree_t{120}),
                              cmove(10),
                              cturn(degree_t{120}));
    // clang-format on

    REQUIRE(final.x == Approx(initial.x).margin(delta));
    REQUIRE(final.y == Approx(initial.y).margin(delta));
    REQUIRE(final.th == Approx(initial.th).margin(delta));
  }
}