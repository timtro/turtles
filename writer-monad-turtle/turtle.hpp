#pragma once

#include "Writer.hpp"
#include <units.h>

#define DISABLE_PREDEFINED_UNITS
#define ENABLE_ANGLE_UNITS
using units::angle::degree_t;

struct Pose {
  const double x{0}, y{0};
  const degree_t th{0};
};

Writer<Pose> move(double, const Pose &);
Writer<Pose> turn(degree_t, const Pose &);