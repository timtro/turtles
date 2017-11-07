#pragma once

#include "../include/tfunc/function_traits.hpp"

#include <functional>
#include <variant>

using trait::invoke_result_t;

// Error type is fixed in the monad.
template <typename T, typename ErrType>
using Either = std::variant<T, ErrType>;

// Monadic bind for the Either monad:
//   mbind :: EirtherM<A> → (A → EitherM<B>) → EitherN<B>
// where
//   EitherM<T> = std::variant<T, errorType>
// Expect the payload to be the first (0th) term in the variant type.
// Expect the error type to be the second term in the variant type:
template <typename EitherMA, typename F>
auto mbind(EitherMA m, F f) {
  // Derive the return type by invoking f on the 0th type in EitherMA:
  using EitherMB = invoke_result_t<F, std::variant_alternative_t<0, EitherMA>>;
  using ErrType = std::variant_alternative_t<1, EitherMA>;
  if (std::holds_alternative<ErrType>(m))
    return static_cast<EitherMB>(m);
  else
    return std::invoke(f, std::get<0>(m));
}

template <typename EitherM, typename F>
auto operator|(EitherM &&m, F &&f) {
  return mbind(std::forward<EitherM>(m), std::forward<F>(f));
}