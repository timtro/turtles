#pragma once

#include "../include/Pose.hpp"

Pose move(meter_t, const Pose &);
Pose turn(degree_t, const Pose &);

// For use in the "dot-style piping" example:
struct TPose : public Pose {
  TPose move(meter_t r) const;
  TPose turn(degree_t dth) const;
};