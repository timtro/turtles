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

template <typename State, typename F>
auto mbind(State m, F f) { // Here, m is a callable.
  return [=](auto stateData) {
    using Action_t = std::invoke_result_t<F, decltype(stateData)>;
    using T = typename Action_t::first_type;
    if (std::holds_alternative<T>(m)) {
      auto &&[retVal, newStateData] = std::invoke(m, stateData);
      return f(retVal)(newStateData);
    } else
      return m;
  };
}

// The mthen function, AKA `>>` is almost identical to mbind, except in the case
// of the State monad, it discards the return value of M<A> so the signature is
// simplified to:
//  mthen : M<A> → M<B> → M<B> = State<Pose, A> → State<Pose, B> → State<Pose,
//  B>
template <typename State, typename F>
auto mthen(State m, F f) {
  return [=](auto stateData) {
    auto &&newStateData = std::invoke(m, stateData).second;
    return f(newStateData);
  };
}

// Mimick Haskell's `do` notation by automatically binding arguments together,
// each of which should be an element in the monad:
template <typename A, typename B>
auto mdo(A &&a, B &&b) {
  return mthen(a, b);
  // Can also implement this with bind if you:
  //          Throw away return values
  //                       V
  // return mbind(a, [=](auto) { return b; });
}

template <typename A, typename... As>
auto mdo(A &&a, As &&... as) {
  return mdo(a, mdo(as...));
}
