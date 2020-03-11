// Object to hold turtle state and implement turtle interface.
//
#pragma once

#include <sstream>

#include "../include/nonconst-Pose.hpp"

class OOTurtle {
  Pose m_pose{meter_t{0}, meter_t{0}, 0_deg};
  std::ostringstream &m_oss;

 public:
  OOTurtle(std::ostringstream &);
  void move(meter_t);
  void turn(degree_t);

  decltype(Pose::x) get_x() const { return this->m_pose.x; }
  decltype(Pose::y) get_y() const { return this->m_pose.y; }
  decltype(Pose::th) get_th() const { return this->m_pose.th; }
};

class MovingError : public std::exception {
  const char *what() const noexcept override {
    return "An exceptional event occurred while moving";
  }
};

class TurningError : public std::exception {
  const char *what() const noexcept override {
    return "An exceptional event occurred while turning";
  }
};
