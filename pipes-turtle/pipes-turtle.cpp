#include "Pose.hpp"

#include <catch/catch.hpp>

TEST_CASE("Equilateral triangle movement should leave invariant Pose, using "
          "crude function interface") {

  Pose initial{0, 0, degree_t{0}};
  const auto s1 = move(initial, 10);
  const auto s2 = turn(s1, degree_t{120});
  const auto s3 = move(s2, 10);
  const auto s4 = turn(s3, degree_t{120});
  const auto s5 = move(s4, 10);
  const auto final = turn(s5, degree_t{120});

  REQUIRE(final.x == Approx(initial.x));
  REQUIRE(final.y == Approx(initial.y));
  REQUIRE(final.th == Approx(initial.th));
}

TEST_CASE("Equilateral triangle movement should leave invariant Pose, using "
          "dot-style-piping.") {
  Pose initial{0, 0, degree_t{0}};
  const auto final = move(initial, 10)
                         .turn(degree_t{120})
                         .move(10)
                         .turn(degree_t{120})
                         .move(10)
                         .turn(degree_t{120});
  REQUIRE(final.x == Approx(initial.x));
  REQUIRE(final.y == Approx(initial.y));
  REQUIRE(final.th == Approx(initial.th));
}