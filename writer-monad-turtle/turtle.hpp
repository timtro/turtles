#pragma once

#include "../include/Pose.hpp"
#include "writer-monad.hpp"

Writer<Pose> move(meter_t, const Pose &);
Writer<Pose> turn(degree_t, const Pose &);
