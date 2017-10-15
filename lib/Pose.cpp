#include "Pose.hpp"

std::ostream &operator<<(std::ostream &os, const Pose &p) {
  os << '[' << p.x << ", " << p.y << ", " << p.th << ']';
  return os;
}