#include "Pose.hpp"

#include <functional>

using units::math::cos;
using units::math::sin;

constexpr bool shitHappens = false;

StateWith<EitherErrorOr<double>> move(double r, const Pose &p0) {
  if (shitHappens)
    return {0, turtleError::hitWall};
  else {
    const auto dx = r * cos(p0.th);
    const auto dy = r * sin(p0.th);
    return {r, p0.x + dx, p0.y + dy, p0.th});
  }
}

StateWith<EitherErrorOr<degree_t>> turn(degree_t dth, const Pose &p0) {
  if (shitHappens)
    return {degree_t{0}, turtleError::couldNotRotate};
  else
    return {dth, {p0.x, p0.y, degree_t{std::fmod((p0.th + dth)(), 360)}}};
}