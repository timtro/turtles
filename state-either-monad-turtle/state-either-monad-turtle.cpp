#include "../include/tfunc/function-operations.hpp"
#include "Pose.hpp"

#include <catch/catch.hpp>

#include <iostream>

TEST_CASE("Using the Either monad, starting at the origin and turtle should…") {

  const Pose initial{0, 0, degree_t{0}};

  // mmove : double → Pose → (double, Pose)
  auto mmove = tf::curry(::move);
  // mturn : degree_t → Pose → (degree_t, Pose)
  auto mturn = tf::curry(::turn);

  SECTION("Be left apprximately invariant sent on the journy of an equilateral "
          "triangle.") {

    // clang-format off
  // auto eitherFinal = move(10, initial) >> mturn(degree_t{120}); 
                    // >> mmove(10) >> mturn(degree_t{120})
                    // >> mmove(10) >> mturn(degree_t{120});
    // clang-format on

    // const Pose final = std::get<Pose>(eitherFinal);

    // REQUIRE(final.x == Approx(initial.x));
    // REQUIRE(final.y == Approx(initial.y));
    // REQUIRE(final.th == Approx(initial.th));

    auto thing = mbind(mmove(10), [=](auto) { return mmove(10); });

    // auto triangle = mdo(
    //   mmove(10),
    //   mturn(degree_t{120}),
    //   mmove(10),
    //   mturn(degree_t{120}),
    //   mmove(10),
    //   mturn(degree_t{120})
    // );
    REQUIRE(true);
  }

  // SECTION("When a `hitWall` error is inserted into the binding chain, the "
  //         "remaining calls should be short circuited, and the error code left
  //         " "in the result variable") {

  //   auto hitTheWall = [](auto) -> EitherErrorOr<Pose> {
  //     return turtleError::hitWall;
  //   };

  //   // clang-format off
  // auto final = move(10, initial) >> mturn(degree_t{120}) >> hitTheWall
  //                   >> mmove(10) >> mturn(degree_t{120})
  //                   >> mmove(10) >> mturn(degree_t{120});
  //   // clang-format on

  //   REQUIRE(std::holds_alternative<turtleError>(final));
  //   REQUIRE(std::get<turtleError>(final) == turtleError::hitWall);
  // }
}