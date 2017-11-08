#pragma once

#include <sstream>
#include <units.h>

#define DISABLE_PREDEFINED_UNITS
#define ENABLE_ANGLE_UNITS

using namespace units::literals;
using units::angle::degree_t;
using units::length::meter_t;

struct Pose {
  const meter_t x{0}, y{0};
  const degree_t th{0};

  friend std::ostream &operator<<(std::ostream &os, const Pose &p) {
    os << '[' << p.x << ", " << p.y << ", " << p.th << ']';
    return os;
  }
};