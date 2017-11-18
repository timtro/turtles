#include "turtle.hpp"
#include <sstream>

using units::math::cos;
using units::math::sin;

constexpr bool exceptionalError{false};

WriterWith<ErrorOr<Pose>> move(meter_t r, const Pose &p0) {
  std::stringstream log;
  if (exceptionalError) {
    log << "hitWall\n";
    return {turtleError::hitWall, log.str()};
  } else {
    const auto dx = r * cos(p0.th);
    const auto dy = r * sin(p0.th);
    auto finalPose = Pose{p0.x + dx, p0.y + dy, p0.th};
    log << "moving from " << p0 << " to " << finalPose << '\n';
    return {finalPose, log.str()};
  }
}

WriterWith<ErrorOr<Pose>> turn(degree_t dth, const Pose &p0) {
  std::stringstream log;
  if (exceptionalError) {
    log << "couldNotRotate\n";
    return {turtleError::couldNotRotate, log.str()};
  } else {
    Pose finalPose = {p0.x, p0.y, degree_t{std::fmod((p0.th + dth)(), 360)}};
    log << "turning from " << p0 << " to " << finalPose << '\n';
    return {finalPose, log.str()};
  }
}