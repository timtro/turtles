#include <functional>
#include <tuple>
#include <variant>

#include "../tfunc/include/function_traits.hpp"

using trait::invoke_result_t;

template <typename StateMA, typename F>
auto mbind(StateMA ma, F f) {
  // ma :: StateMonad<A> = State → StateWith<ErrorOr<A>>,
  //  f :: F = A → StateMonad<B> - A → State → StateWith<ErrorOr<B>>.
  return [=](auto state) {
    auto maResult = std::invoke(ma, state);
    // Deduce output types:
    using StateWithErrorOrB =
        invoke_result_t<invoke_result_t<F, decltype(maResult.first)>,
                        decltype(maResult.second)>;
    using ErrType =
        typename std::variant_alternative_t<1,
                                            decltype(StateWithErrorOrB::first)>;

    if (std::holds_alternative<ErrType>(maResult.first)) {
      // Since both paths out of this function have to return the same type, we
      // have to convert StateWith<ErrorOr<A> into
      // StateWith<ErrorOr<B>, even though we are certain that it's an
      // ErrType, and not an A or a B. Otherwise, we could return maResult.
      StateWithErrorOrB b =
          std::make_pair(std::get<ErrType>(maResult.first), maResult.second);
      return b;
    } else
      return f(maResult.first)(maResult.second);
  };
}

template <typename StateM, typename F>
auto operator|(StateM &&m, F &&f) {
  return mbind(std::forward<StateM>(m), std::forward<F>(f));
}

// TODO: When the ErrType type-variable is working in mbind, use it here too.
template <class StateMA, class StateMB>
auto mthen(StateMA ma, StateMB mb) {
  return [=](auto state) {
    auto maResult = std::invoke(ma, state);
    using StateWithErrorOrB =
        invoke_result_t<StateMB, decltype(maResult.second)>;
    using ErrType =
        typename std::variant_alternative_t<1,
                                            decltype(StateWithErrorOrB::first)>;
    if (std::holds_alternative<ErrType>(maResult.first)) {
      StateWithErrorOrB b =
          std::make_pair(std::get<ErrType>(maResult.first), maResult.second);
      return b;
    } else
      return mb(maResult.second);
  };
}

template <class StateMA, class StateMB>
auto operator>>(StateMA ma, StateMB mb) {
  return mthen(std::forward<StateMA>(ma), std::forward<StateMB>(mb));
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
