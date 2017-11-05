#include "turtle.hpp"
#include <sstream>

using units::math::cos;
using units::math::sin;

Writer<Pose> move(double r, const Pose &p0) {
  std::stringstream log;
  const auto dx = r * cos(p0.th);
  const auto dy = r * sin(p0.th);
  auto finalPose = Pose{p0.x + dx, p0.y + dy, p0.th};
  log << "moving from " << p0 << " to " << finalPose << '\n';
  return {finalPose, log.str()};
}

Writer<Pose> turn(degree_t dth, const Pose &p0) {
  std::stringstream log;
  Pose finalPose = {p0.x, p0.y, degree_t{std::fmod((p0.th + dth)(), 360)}};
  log << "turning from " << p0 << " to " << finalPose << '\n';
  return {finalPose, log.str()};
}