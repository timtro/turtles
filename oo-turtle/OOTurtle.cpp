#include "OOTurtle.hpp"
#include <iostream>

using units::math::sin;
using units::math::cos;

// TODO: Replace cout with boost.Log2

Pose advanced_position(Pose x0, int r) {
  auto dx = r * cos(x0.th);
  auto dy = r * sin(x0.th);
  return {x0.x + dx, x0.y + dy, x0.th};
}

void OOTurtle::move(int r) {
  this->m_pose = advanced_position(this->m_pose, r);
  // clang-format off
  std::cout << "advancing to: [" 
            << this->m_pose.x << ", "
            << this->m_pose.y << ", "
            << this->m_pose.th << "]\n";
  // clang-format on
}

void OOTurtle::turn(degree_t dth) {
  this->m_pose.th += dth;
  // clang-format off
  std::cout << "turning to: [" 
            << this->m_pose.x << ", "
            << this->m_pose.y << ", "
            << this->m_pose.th << "]\n";
  // clang-format on
}