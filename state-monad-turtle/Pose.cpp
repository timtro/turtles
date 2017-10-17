#include "Pose.hpp"

using units::math::sin;
using units::math::cos;

// Monadic versions of the turtle functions

// Examine the state at this point in the computation.
auto mget() {
  return [](auto s) { return std::make_pair(s, s); };
}

StateWith<double> move(double r, const Pose &p0) {
  const auto dx = r * cos(p0.th);
  const auto dy = r * sin(p0.th);
  return {r, {p0.x + dx, p0.y + dy, p0.th}};
}

StateWith<degree_t> turn(degree_t dth, const Pose &p0) {
  return {dth, {p0.x, p0.y, degree_t{std::fmod((p0.th + dth)(), 360)}}};
}
