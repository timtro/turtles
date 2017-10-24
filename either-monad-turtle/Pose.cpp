#include "Pose.hpp"

#include <functional>

using units::math::cos;
using units::math::sin;

constexpr bool shitHappens = false;

EitherErrorOr<Pose> move(double r, const Pose &p0) {
  if (shitHappens)
    return turtleError::hitWall;
  else {
    const auto dx = r * cos(p0.th);
    const auto dy = r * sin(p0.th);
    return Pose{p0.x + dx, p0.y + dy, p0.th};
  }
}

EitherErrorOr<Pose> turn(degree_t dth, const Pose &p0) {
  if (shitHappens)
    return turtleError::couldNotRotate;
  else
    return Pose{p0.x, p0.y, degree_t{std::fmod((p0.th + dth)(), 360)}};
}