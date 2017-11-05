#include <tuple>
#include <functional>
#include "../include/Pose.hpp"

// Functions supporting the State-Monad for the Turtle application.
//
// mreturn :
template <typename A>
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
template <typename State, typename F>
auto mbind(State m, F f) {
  return [=](auto stateData) {
    // Once given state data, run the State and unpack the result
    auto &&[retVal, newStateData] = std::invoke(m, stateData);
    // forward the result to the (A → M<B>) function.
    return f(retVal)(newStateData);
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
