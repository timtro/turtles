#include "../include/tfunc/function-operations.hpp"
#include "Pose.hpp"

#include <catch/catch.hpp>

TEST_CASE("Equilateral triangle movement should leave invariant Pose, using "
          "crude function interface") {

  Pose initial{0, 0, degree_t{0}};
  const auto s1 = move(10, initial);
  const auto s2 = turn(degree_t{120}, s1);
  const auto s3 = move(10, s2);
  const auto s4 = turn(degree_t{120}, s3);
  const auto s5 = move(10, s4);
  const auto final = turn(degree_t{120}, s5);

  REQUIRE(final.x == Approx(initial.x));
  REQUIRE(final.y == Approx(initial.y));
  REQUIRE(final.th == Approx(initial.th));
}

TEST_CASE("Equilateral triangle movement should leave invariant Pose, using "
          "dot-style-piping.") {

  Pose initial{0, 0, degree_t{0}};
  const auto final = move(10, initial)
                         .turn(degree_t{120})
                         .move(10)
                         .turn(degree_t{120})
                         .move(10)
                         .turn(degree_t{120});

  REQUIRE(final.x == Approx(initial.x));
  REQUIRE(final.y == Approx(initial.y));
  REQUIRE(final.th == Approx(initial.th));
}

TEST_CASE("Equilateral triangle movement should leave invariant Pose, using "
          "curried functions and pipes.") {

  Pose initial{0, 0, degree_t{0}};
  auto cmove = tf::curry(::move);
  auto cturn = tf::curry(::turn);

  // clang-format off
  const auto final = tf::pipe(initial,
                              cmove(10),
                              cturn(degree_t{120}),
                              cmove(10),
                              cturn(degree_t{120}),
                              cmove(10),
                              cturn(degree_t{120}));
  // clang-format on

  REQUIRE(final.x == Approx(initial.x));
  REQUIRE(final.y == Approx(initial.y));
  REQUIRE(final.th == Approx(initial.th));
}