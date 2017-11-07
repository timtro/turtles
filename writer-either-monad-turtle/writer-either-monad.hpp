#pragma once

#include "../include/tfunc/function_traits.hpp"

#include <functional>
#include <string>
#include <tuple>
#include <variant>

using trait::invoke_result_t;

template <typename T>
using WriterWith = std::pair<T, std::string>;

// Error type is fixed in the monad.
template <typename T, typename ErrType>
using Either = std::variant<T, ErrType>;

// Monadic bind for the Either monad:
//   mbind :: EirtherM<A> → (A → EitherM<B>) → EitherN<B>
// where
//   EitherM<T> = std::variant<T, errorType>
// Expect the payload of the Writer to be in the first in the pair
// Epxect the log to be second in the pair.
// Expect the payload of Either to be the first (0th) term in the variant type.
// Expect the error type of Either to be the second term in the variant type:
template <typename WriterEitherMA, typename F>
auto mbind(WriterEitherMA m, F f) {
  using EitherA = typename WriterEitherMA::first_type;
  using ErrType = std::variant_alternative_t<1, EitherA>;
  using WriterEitherMB =
      invoke_result_t<F, std::variant_alternative_t<0, EitherA>>;

  if (std::holds_alternative<ErrType>(m.first))
    return static_cast<WriterEitherMB>(m);
  else {
    auto [mResult, resultLog] = std::invoke(f, std::get<0>(m.first));
    return WriterEitherMB{mResult, m.second + resultLog};
  }
}

template <typename EitherM, typename F>
auto operator|(EitherM &&m, F &&f) {
  return mbind(std::forward<EitherM>(m), std::forward<F>(f));
}