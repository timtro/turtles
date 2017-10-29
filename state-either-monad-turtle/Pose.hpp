#pragma once

#include <functional>
#include <units.h>
#include <variant>

#include "../include/tfunc/function_traits.hpp"

#define DISABLE_PREDEFINED_UNITS
#define ENABLE_ANGLE_UNITS
using units::angle::degree_t;

using trait::invoke_result_t;

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
  // ma :: StateMonad<A> = State → StateWith<EitherErrorOr<A>>,
  //  f :: F = A → StateMonad<B> - A → State → StateWith<EitherErrorOr<B>>.
  return [=](auto state) {

    auto maResult = std::invoke(ma, state);
    // Deduce output types:
    using StateWithEitherErrorOrB =
        invoke_result_t<invoke_result_t<F, decltype(maResult.first)>,
                        decltype(maResult.second)>;
    using ErrType = typename std::variant_alternative_t<
        1, decltype(StateWithEitherErrorOrB::first)>;

    if (std::holds_alternative<ErrType>(maResult.first)) {
      // Since both paths out of this function have to return the same type, we
      // have to convert StateWith<EitherErrorOr<A> into
      // StateWith<EitherErrorOr<B>, even though we are certain that it's an
      // ErrType, and not an A or a B. Otherwise, we could return maResult.
      StateWithEitherErrorOrB b =
          std::make_pair(std::get<ErrType>(maResult.first), maResult.second);
      return b;
    } else
      return f(maResult.first)(maResult.second);
  };
}

// TODO: When the ErrType type-variable is working in mbind, use it here too.
template <class StateMA, class StateMB>
auto mthen(StateMA ma, StateMB mb) {
  return [=](auto state) {
    auto maResult = std::invoke(ma, state);
    using StateWithEitherErrorOrB =
        invoke_result_t<StateMB, decltype(maResult.second)>;
    using ErrType = typename std::variant_alternative_t<
        1, decltype(StateWithEitherErrorOrB::first)>;
    if (std::holds_alternative<ErrType>(maResult.first)) {
      StateWithEitherErrorOrB b =
          std::make_pair(std::get<ErrType>(maResult.first), maResult.second);
      return b;
    } else
      return mb(maResult.second);
  };
}

template <class StateMA, class StateMB>
auto operator>>(StateMA ma, StateMB mb) {
  return mthen(ma, mb);
  // return mbind(ma, [=](auto) { return mb; });
}

// Mimick Haskell's `do` notation by automatically binding arguments together,
// each of which should be an element in the monad:
template <typename StateMA, typename StateMB>
auto mdo(StateMA &&ma, StateMB &&mb) {
  return mthen(ma, mb);
  // return mbind(ma, [=](auto) { return mb; });
}

template <typename StateMA, typename... StateMs>
auto mdo(StateMA &&a, StateMs &&... ms) {
  return mdo(a, mdo(ms...));
}
