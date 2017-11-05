#pragma once

#include <sstream>
#include <units.h>

#define DISABLE_PREDEFINED_UNITS
#define ENABLE_ANGLE_UNITS
using units::angle::degree_t;

struct Pose {
  double x{0}, y{0};
  degree_t th{0};
};

std::ostream &operator<<(std::ostream &, const Pose &);