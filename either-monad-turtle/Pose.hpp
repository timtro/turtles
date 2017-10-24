#pragma once

#include <functional>
#include <units.h>
#include <variant>

#define DISABLE_PREDEFINED_UNITS
#define ENABLE_ANGLE_UNITS
using units::angle::degree_t;

enum class turtleError { hitWall, couldNotRotate };

template <typename T>
using EitherErrorOr = std::variant<T, turtleError>;

struct Pose {
  const double x{0}, y{0};
  const degree_t th{0};
};

EitherErrorOr<Pose> move(double, const Pose &);
EitherErrorOr<Pose> turn(degree_t, const Pose &);

// I normally wouldn't use >>, since >>= is more traditional (in Haskell) but >>
// has the correct precedence and association direction.
template <typename T, typename F>
auto operator>>(EitherErrorOr<T> m, F f)
    -> decltype(std::invoke(f, std::get<T>(m))) {
  if (std::holds_alternative<T>(m))
    return std::invoke(f, std::get<T>(m));
  else
    return m;
}