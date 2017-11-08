#pragma once

#include "writer-monad.hpp"
#include "../include/Pose.hpp"

Writer<Pose> move(meter_t, const Pose &);
Writer<Pose> turn(degree_t, const Pose &);