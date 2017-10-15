// Object to hold turtle state and implement turtle interface.
//
#pragma once

#include <sstream>
#include <units.h>

#define DISABLE_PREDEFINED_UNITS
#define ENABLE_ANGLE_UNITS
using units::angle::degree_t;

struct Pose {
  int x{0}, y{0};
  degree_t th{0};
};

class OOTurtle {
  Pose m_pose{0, 0, degree_t{0}};
  std::ostringstream &m_oss;

public:
  OOTurtle() = default;
  OOTurtle(std::ostringstream &);
  void move(int r);
  void turn(degree_t);
};