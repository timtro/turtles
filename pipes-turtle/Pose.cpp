#include "Pose.hpp"

using units::math::sin;
using units::math::cos;

Pose move(const Pose &p0, double r) {
  const auto dx = r * cos(p0.th);
  const auto dy = r * sin(p0.th);
  return {p0.x + dx, p0.y + dy, p0.th};
}

Pose turn(const Pose &p0, degree_t dth) {
  return {p0.x, p0.y, degree_t{std::fmod((p0.th + dth)(), 360)}};
}