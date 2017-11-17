#pragma once

#include "../include/nonconst-Pose.hpp"
#include "writer-class.hpp"

Writer<Pose> move(meter_t, const Pose &);
Writer<Pose> turn(degree_t, const Pose &);