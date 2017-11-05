#include "OOTurtle.hpp"

using units::math::cos;
using units::math::sin;

constexpr bool exceptionalError{false};

OOTurtle::OOTurtle(std::ostringstream &oss) : m_oss(oss) {}

Pose advanced_position(Pose x0, int r) {
  auto dx = r * cos(x0.th);
  auto dy = r * sin(x0.th);
  return {x0.x + dx, x0.y + dy, x0.th};
}

void OOTurtle::move(int r) {
  if (exceptionalError)
    throw MovingError();
  m_oss << "moving from " << this->m_pose;
  this->m_pose = advanced_position(this->m_pose, r);
  m_oss << " to " << this->m_pose << '\n';
}

void OOTurtle::turn(degree_t dth) {
  if (exceptionalError)
    throw TurningError();
  m_oss << "turning from " << this->m_pose;
  this->m_pose.th += dth;
  this->m_pose.th = degree_t{std::fmod(this->m_pose.th(), 360)};
  m_oss << " to " << this->m_pose << '\n';
}