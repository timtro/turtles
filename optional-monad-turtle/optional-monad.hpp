#pragma once

#include <functional>
#include <optional>

// I normally wouldn't use >>, since >>= is more traditional (in Haskell) but >>
// has the correct precedence and association.
template <typename T, typename F>
auto mbind(std::optional<T> m, F f) -> decltype(std::invoke(f, *m)) {
  if (m)
    return std::invoke(f, *m);
  else
    return {};
}

// Infix interface for mbind:
template <typename WriterM, typename F>
auto operator|(WriterM &&m, F &&f) {
  return mbind(std::forward<WriterM>(m), std::forward<F>(f));
}
