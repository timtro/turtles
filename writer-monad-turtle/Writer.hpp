#pragma once

#include <functional>
#include <string>
#include <tuple>

template <typename T>
using Writer = std::pair<T, std::string>;

// mbind : M<A> → (A → M<B>) → M<B>
template <typename WriterM, typename F>
auto mbind(WriterM m, F f) {
  auto [mResult, resultLog] = std::invoke(f, m.first);
  return std::make_pair(mResult, m.second + resultLog);
}

// Infix interface for mbind:
template <typename WriterM, typename F>
auto operator|(WriterM &&m, F &&f) {
  return mbind(std::forward<WriterM>(m), std::forward<F>(f));
}