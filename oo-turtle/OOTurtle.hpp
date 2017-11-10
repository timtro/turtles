// Object to hold turtle state and implement turtle interface.
//
#pragma once

#include "../include/nonconst-Pose.hpp"
#include <sstream>

class OOTurtle {
  Pose m_pose{meter_t{0}, meter_t{0}, 0_deg};
  std::ostringstream &m_oss;

public:
  OOTurtle() = default;
  OOTurtle(std::ostringstream &);
  void move(meter_t);
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

class TurningError : public std::exception {
  const char *what() const noexcept override {
    return "An exceptional event occured while turning";
  }
};