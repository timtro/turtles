#include "turtle.hpp"

using units::math::cos;
using units::math::sin;

constexpr bool exceptionalError{false};

StateWith<ErrorOr<meter_t>> move(meter_t r, const Pose &p0) {
  if (exceptionalError)
    return {turtleError::hitWall, p0};
  else {
    const auto dx = r * cos(p0.th);
    const auto dy = r * sin(p0.th);
    return {r, {p0.x + dx, p0.y + dy, p0.th}};
  }
}

StateWith<ErrorOr<degree_t>> turn(degree_t dth, const Pose &p0) {
  if (exceptionalError)
    return {turtleError::couldNotRotate, p0};
  else
    return {dth, {p0.x, p0.y, degree_t{std::fmod((p0.th + dth)(), 360)}}};
}