#pragma once

#include <functional>
#include <units.h>
#include <variant>

#define DISABLE_PREDEFINED_UNITS
#define ENABLE_ANGLE_UNITS
using units::angle::degree_t;

struct Pose {
  const double x{0}, y{0};
  const degree_t th{0};
};

enum class turtleError { hitWall, couldNotRotate };

template <typename T>
using EitherErrorOr = std::variant<T, turtleError>;

template <typename T>
using StateWith = std::pair<T, Pose>;

StateWith<EitherErrorOr<double>> move(double, const Pose &);
StateWith<EitherErrorOr<degree_t>> turn(degree_t, const Pose &);

template <typename StateMA, typename F>
auto mbind(StateMA ma, F f) {
  // a :: StateMonad<A> = State → StateWith<A>,
  // f :: F = A → State → StateWith<B> = A → StateMonad<B>.
  return [=](auto state) {
    auto maResult = std::invoke(ma, state);
    using StateWithEitherErrorOrB =
        std::invoke_result_t<std::invoke_result_t<F, decltype(maResult.first)>,
                             decltype(maResult.second)>;
    // Get this working
    // using ErrType = typename std::variant_alternative<
    //     1, decltype(StateWithEitherErrorOrB::first_type)>::type;
    if (std::holds_alternative<turtleError>(maResult.first)) {
      // This nasty but of code just converts an M<A+err> with an error to an
      // M<B+err>.
      StateWithEitherErrorOrB b = std::make_pair(
          std::get<turtleError>(maResult.first), maResult.second);
      return b;
    } else
      return f(maResult.first)(maResult.second);
  };
}

template <class StateMA, class StateMB>
auto mthen(StateMA ma, StateMB mb) {
  return [=](auto state) {
    auto maResult = std::invoke(ma, state);
    using StateWithEitherErrorOrB =
        std::invoke_result_t<StateMB, decltype(maResult.second)>;
    if (std::holds_alternative<turtleError>(maResult.first)) {
      StateWithEitherErrorOrB b = std::make_pair(
          std::get<turtleError>(maResult.first), maResult.second);
      return b;
    } else
      return mb(maResult.second);
  };
}

template <class StateMA, class StateMB>
auto operator>>(StateMA ma, StateMB mb) {
  return mthen(ma, mb);
}

// Mimick Haskell's `do` notation by automatically binding arguments together,
// each of which should be an element in the monad:
template <typename A, typename B>
auto mdo(A &&a, B &&b) {
  return mthen(a, b);
}

template <typename A, typename... As>
auto mdo(A &&a, As &&... as) {
  return mdo(a, mdo(as...));
}
