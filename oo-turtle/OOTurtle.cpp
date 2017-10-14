#include "OOTurtle.hpp"

using units::math::sin;
using units::math::cos;

// TODO: Replace oss with boost.Log2

std::ostream& operator<<(std::ostream& os, const Pose& p)  
{  
  // clang-format off
  os << '[' 
      << p.x << ", "
      << p.y << ", "
      << p.th << ']';  
  // clang-format on
  return os;  
} 

OOTurtle::OOTurtle(std::ostringstream& oss) : m_oss(oss) {}

Pose advanced_position(Pose x0, int r) {
  auto dx = r * cos(x0.th);
  auto dy = r * sin(x0.th);
  return {x0.x + dx, x0.y + dy, x0.th};
}

void OOTurtle::move(int r) {
  m_oss << "advancing from " <<  this->m_pose;
  this->m_pose = advanced_position(this->m_pose, r);
  m_oss << " to " <<  this->m_pose << '\n';
  
}

void OOTurtle::turn(degree_t dth) {
  m_oss << "turning from " << this->m_pose;   
  this->m_pose.th += dth;
  this->m_pose.th = degree_t{std::fmod(this->m_pose.th(), 360)};
  m_oss << " to " <<  this->m_pose << '\n';
  
}