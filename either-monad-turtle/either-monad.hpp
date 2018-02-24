#pragma once

#include "../include/tfunc/function_traits.hpp"

#include <functional>
#include <variant>

// Error type is fixed in the monad:
// class Monad m => MonadError e m | m -> e where
template <typename ErrType, typename T>
using MonadError = std::variant<ErrType, T>;

// mbind :: ErrorOr<A> → (A → ErrorOr<B>) → ErrorOr<B>
template <typename ErrOrA, typename F>
auto mbind(ErrOrA m, F f) {
  using ErrType = std::variant_alternative_t<0, ErrOrA>;
  using ErrOrB = std::invoke_result_t<F, std::variant_alternative_t<1, ErrOrA>>;
  if (std::holds_alternative<ErrType>(m))
    return static_cast<ErrOrB>(m);
  else
    return std::invoke(f, std::get<1>(m));
}

template <typename ErrOrA, typename F>
auto operator|(ErrOrA &&m, F &&f) {
  return mbind(std::forward<ErrOrA>(m), std::forward<F>(f));
}