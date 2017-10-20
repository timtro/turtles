#pragma once

#include <functional>
#include <optional>
#include <units.h>

#define DISABLE_PREDEFINED_UNITS
#define ENABLE_ANGLE_UNITS
using units::angle::degree_t;

struct Pose {
  const double x{0}, y{0};
  const degree_t th{0};
};

std::optional<Pose> move(double, const Pose &);
std::optional<Pose> turn(degree_t, const Pose &);

// I normally wouldn't use >>, since >>= is more traditional (in Haskell) but >>
// has the correct precedence and association.
template <typename T, typename F>
auto operator>>(std::optional<T> m, F f) -> decltype(std::invoke(f, *m)) {
  if (m)
    return std::invoke(f, *m);
  else
    return {};
}