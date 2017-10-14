#pragma once

#include <units.h>

using units::angle::degree_t;

struct Pose {
  int x{0}, y{0};
  degree_t th{0};
};

class OOTurtle {
  Pose m_pose{0, 0, degree_t{0}};

public:
  void move(int r);
  void turn(degree_t);
};