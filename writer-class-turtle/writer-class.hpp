#pragma once

#include <functional>
#include <sstream>
#include <string>

template <typename A>
struct Writer {
  const A value;
  const std::string log;

  Writer() = delete;
};

// A helper to build an immutable writer type in stages.
template <typename A>
struct WriterBuilder {
  A value;
  std::stringstream log;

  auto build() const {
    // Validation here if needed
    return Writer<A>{value, log.str()};
  }
};

template <typename A>
Writer<A> pure(const A &&a) {
  return Writer{a, ""};
}

// mbind : M<A> → (A → M<B>) → M<B>
template <typename WriterM, typename F>
auto mbind(WriterM m, F f) {
  auto mResult = std::invoke(f, m.value);
  return Writer<decltype(mResult.value)>{mResult.value, m.log + mResult.log};
}

// Infix interface for mbind:
template <typename WriterM, typename F>
auto operator|(WriterM &&m, F &&f) {
  return mbind(std::forward<WriterM>(m), std::forward<F>(f));
}