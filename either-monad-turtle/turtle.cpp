#include "turtle.hpp"

using units::math::cos;
using units::math::sin;

constexpr bool exceptionalError{false};

ErrorOr<Pose> move(meter_t r, const Pose &p0) {
  if (exceptionalError)
    return {turtleError::hitWall};
  else {
    const auto dx = r * cos(p0.th);
    const auto dy = r * sin(p0.th);
    return Pose{p0.x + dx, p0.y + dy, p0.th};
  }
}

ErrorOr<Pose> turn(degree_t dth, const Pose &p0) {
  if (exceptionalError)
    return {turtleError::couldNotRotate};
  else
    return Pose{p0.x, p0.y, degree_t{std::fmod((p0.th + dth)(), 360)}};
}
