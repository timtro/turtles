#pragma once

#include <sstream>
#include <units.h>

using namespace units::literals;
using units::angle::degree_t;
using units::length::meter_t;

// In the global version in ../include/Pose.hpp, the fields of Pose are const,
// and the Pose in an immutable data structure. In the OO version that isn't
// possible.
struct Pose {
  meter_t x{0}, y{0};
  degree_t th{0};

  friend std::ostream &operator<<(std::ostream &os, const Pose &p) {
    os << '[' << p.x << ", " << p.y << ", " << p.th << ']';
    return os;
  }
};