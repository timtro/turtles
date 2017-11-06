#pragma once

#include "../include/tfunc/function_traits.hpp"

#include <functional>
#include <variant>

using trait::invoke_result_t;

template <typename EitherMA, typename F>
auto mbind(EitherMA m, F f) {
  using ErrType = std::variant_alternative_t<1, EitherMA>;
  using EitherMB = invoke_result_t<F, std::variant_alternative_t<0, EitherMA>>;
  if (std::holds_alternative<ErrType>(m))
    return EitherMB{m};
  else
    return std::invoke(f, std::get<0>(m));
}

template <typename EitherM, typename F>
auto operator|(EitherM &&m, F &&f) {
  return mbind(std::forward<EitherM>(m), std::forward<F>(f));
}