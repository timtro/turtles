#include "Pose.hpp"

#include <functional>

using units::math::cos;
using units::math::sin;

constexpr bool shitHappens = false;

std::optional<Pose> move(double r, const Pose &p0) {
  if (shitHappens)
    return {};
  else {
    const auto dx = r * cos(p0.th);
    const auto dy = r * sin(p0.th);
    return Pose{p0.x + dx, p0.y + dy, p0.th};
  }
}

std::optional<Pose> turn(degree_t dth, const Pose &p0) {
  if (shitHappens)
    return {};
  else
    return Pose{p0.x, p0.y, degree_t{std::fmod((p0.th + dth)(), 360)}};
}