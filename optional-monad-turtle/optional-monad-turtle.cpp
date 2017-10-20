#include "../include/tfunc/function-operations.hpp"
#include "Pose.hpp"

#include <catch/catch.hpp>

#include <iostream>

TEST_CASE("Equilateral triangle movement should leave invariant Pose, using "
          "optional monad and >>= style binding.") {

  Pose initial{0, 0, degree_t{0}};

  // mmove : double → Pose → (double, Pose)
  auto mmove = tf::curry(::move);
  // mturn : degree_t → Pose → (degree_t, Pose)
  auto mturn = tf::curry(::turn);

  // clang-format off
  auto final = move(10, initial) >> mturn(degree_t{120}) 
                    >> mmove(10) >> mturn(degree_t{120})
                    >> mmove(10) >> mturn(degree_t{120});
  // clang-format on

  REQUIRE(final->x == Approx(initial.x));
  REQUIRE(final->y == Approx(initial.y));
  REQUIRE(final->th == Approx(initial.th));
}

TEST_CASE("Inserting a null unit in the binding chain should short circuit the "
          "rest of the computation, leaving an empty optional result") {

  Pose initial{0, 0, degree_t{0}};

  // mmove : double → Pose → (double, Pose)
  auto mmove = tf::curry(::move);
  // mturn : degree_t → Pose → (degree_t, Pose)
  auto mturn = tf::curry(::turn);

  auto kill = [](auto) -> std::optional<Pose> { return {}; };

  // clang-format off
  auto final = move(10, initial) >> mturn(degree_t{120}) >> kill 
                    >> mmove(10) >> mturn(degree_t{120})
                    >> mmove(10) >> mturn(degree_t{120});
  // clang-format on

  REQUIRE(final.has_value() == false);
}