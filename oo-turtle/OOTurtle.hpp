// Object to hold turtle state and implement turtle interface.
//
#pragma once

#include "../lib/Pose.hpp"
#include <sstream>

class OOTurtle {
  Pose m_pose{0, 0, degree_t{0}};
  std::ostringstream &m_oss;

public:
  OOTurtle() = default;
  OOTurtle(std::ostringstream &);
  void move(int r);
  void turn(degree_t);
};