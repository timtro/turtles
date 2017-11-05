// Object to hold turtle state and implement turtle interface.
//
#pragma once

#include "Pose.hpp"
#include <sstream>

class OOTurtle {
  Pose m_pose{0, 0, degree_t{0}};
  std::ostringstream &m_oss;

public:
  OOTurtle() = default;
  OOTurtle(std::ostringstream &);
  void move(int r);
  void turn(degree_t);

  decltype(Pose::x) get_x() { return this->m_pose.x; }
  decltype(Pose::y) get_y() { return this->m_pose.y; }
  decltype(Pose::th) get_th() { return this->m_pose.th; }
};

class MovingError : public std::exception {
  const char *what() const noexcept override {
    return "An exceptional event occured while moving";
  }
};