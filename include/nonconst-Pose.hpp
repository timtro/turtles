#pragma once

#include <units.h>

#include <sstream>

using namespace units::literals;
using units::angle::degree_t;
using units::length::meter_t;

// Mutable version of pose, where fields aren't const.
struct Pose {
  meter_t x{0}, y{0};
  degree_t th{0};

  friend std::ostream &operator<<(std::ostream &os, const Pose &p) {
    os << '[' << p.x << ", " << p.y << ", " << p.th << ']';
    return os;
  }
};
