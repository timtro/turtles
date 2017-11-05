#pragma once

#include <sstream>
#include <units.h>

#define DISABLE_PREDEFINED_UNITS
#define ENABLE_ANGLE_UNITS
using units::angle::degree_t;

struct Pose;

Pose move(double, const Pose &);
Pose turn(degree_t, const Pose &);

// We could simply inherit from the Pose from ../include/Pose.hpp, but it
// creates a little more complexity than I'd like in a example.
struct Pose {
  const double x{0}, y{0};
  const degree_t th{0};

  // These enable the dot().continuation().style().of().pipes().
  Pose move(double r) { return ::move(r, *this); }
  Pose turn(degree_t dth) { return ::turn(dth, *this); }
};