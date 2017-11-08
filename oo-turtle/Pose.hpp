#pragma once

#include <sstream>
#include <units.h>

#define DISABLE_PREDEFINED_UNITS
#define ENABLE_ANGLE_UNITS
using units::angle::degree_t;

// In the global version in ../include/Pose.hpp, the fields of Pose are const,
// and the Pose in an immutable data structure. In the OO version that isn't
// possible.
struct Pose {
  double x{0}, y{0};
  degree_t th{0};

  friend std::ostream &operator<<(std::ostream &os, const Pose &p) {
    os << '[' << p.x << ", " << p.y << ", " << p.th << ']';
    return os;
  }
};