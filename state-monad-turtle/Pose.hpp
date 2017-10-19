#pragma once

#include <functional>
#include <sstream>
#include <units.h>
#include <utility>

#define DISABLE_PREDEFINED_UNITS
#define ENABLE_ANGLE_UNITS
using units::angle::degree_t;

struct Pose {
  const double x{0}, y{0};
  const degree_t th{0};
};

template <typename T>
using StateWith = std::pair<T, Pose>;

StateWith<double> move(double, const Pose &);
StateWith<degree_t> turn(degree_t, const Pose &);

// Functions supporting the State-Monad for the Turtle application.
//
// mreturn :
template <class A>
auto mreturn(const A &a) {
  return [=](auto stateData) { return std::make_pair(a, stateData); };
}

// Generally, mbind AKA `>>=` has the signature
//   mbind : M<A> → (A → M<B>) → M<B>
// In the specific case of the State monad:
//   M<T> = State<Pose, T> = = Pose → (T, Pose)
// so,
//   mbind : State<Pose, A> → (A → State<Pose, B>) → State<Pose, B>.
// The bind operation gives us function composition. NOTE: I think the
// convention of calling the function type Pose → (T, Pose) a `State` is
// misleading. It should be called a state-function or state-processor.
template <class State, class F>
auto mbind(State m, F f) {
  return [=](auto stateData) {
    // Once given state data, run the State and unpack the result
    auto &&[x, s] = m(stateData);
    // forward the result to the (A → M<B>) function.
    return f(x)(s);
  };
}

// The mthen function, AKA `>>` is almost identical to mbind, except in the case
// of the State monad, it discards the return value of M<A> so the signature is
// simplified to:
//  mthen : M<A> → M<B> → M<B> = State<Pose, A> → State<Pose, B> → State<Pose,
//  B>
template <class State, class F>
auto mthen(State m, F f) {
  return [=](auto stateData) {
    auto &&[x, s] = m(stateData);
    return f(s);
  };
}

// Mimick Haskell's `do` notation by automatically binding arguments together,
// each of which should be an element in the monad:
template <class A, class B>
auto mdo(A &&a, B &&b) {
  return mthen(a, b);
  // Can also implement this with bind if you:
  //          Throw away return values
  //                       V
  // return mbind(a, [=](auto) { return b; });
}

template <class A, class... As>
auto mdo(A &&a, As &&... as) {
  return mdo(a, mdo(as...));
}
