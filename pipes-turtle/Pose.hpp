#pragma once

#include <sstream>
#include <units.h>

#define DISABLE_PREDEFINED_UNITS
#define ENABLE_ANGLE_UNITS
using units::angle::degree_t;

struct Pose;

Pose move(const Pose &, double);
Pose turn(const Pose &, degree_t);

struct Pose {
  const double x{0}, y{0};
  const degree_t th{0};

  // These enable the dot().continuation().style().of().pipes().
  Pose move(double r) { return ::move(*this, r); }
  Pose turn(degree_t dth) { return ::turn(*this, dth); }
};