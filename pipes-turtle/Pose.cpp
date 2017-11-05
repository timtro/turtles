#include "turtle.hpp"

using units::math::cos;
using units::math::sin;

Pose move(double r, const Pose &p0) {
  const auto dx = r * cos(p0.th);
  const auto dy = r * sin(p0.th);
  return {p0.x + dx, p0.y + dy, p0.th};
}

Pose turn(degree_t dth, const Pose &p0) {
  return {p0.x, p0.y, degree_t{std::fmod((p0.th + dth)(), 360)}};
}