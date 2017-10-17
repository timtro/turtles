#pragma once

#include <functional>
#include <sstream>
#include <units.h>
#include <utility>

#define DISABLE_PREDEFINED_UNITS
#define ENABLE_ANGLE_UNITS
using units::angle::degree_t;

struct Pose;

template <typename T>
using M = std::pair<T, Pose>;

M<double> move(double, const Pose &);
M<degree_t> turn(degree_t, const Pose &);

struct Pose {
  const double x{0}, y{0};
  const degree_t th{0};

  // These enable the dot().continuation().style().of().pipes().
  M<double> move(double r) { return ::move(r, *this); }
  M<degree_t> turn(degree_t dth) { return ::turn(dth, *this); }
};

template <class X>
auto mreturn(const X &x) {
  return [=](auto s) { return std::make_pair(x, s); };
}

// Generally,
//   mbind : M<A> → (A → M<B>) → M<B>
// In the specific case of the State monad:
//   M<T> = State<Pose, T> = = Pose → (T, Pose)
// so,
//   mbind : State<Pose, A> → (A → State<Pose, B>) → State<Pose, B>.
// The bind operation gives us function composition.
template <class State, class F>
auto mbind(State m, F f) {
  return [=](auto stateData) {
    // Once given state data, run the State and unpack the result
    auto && [ x, s ] = m(stateData);
    // forward the result to the (A → M<B>) function.
    return f(x)(s);
  };
}

// Mimick Haskell's `do` notation by automatically binding arguments together,
// each of which should be an element in the monad:
template <class X, class Y>
auto mdo(X &&x, Y &&y) {
  return mbind(x, [=](auto) { return y; });
}

template <class X, class... Xs>
auto mdo(X &&x, Xs &&... xs) {
  return mdo(x, mdo(xs...));
}
