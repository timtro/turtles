#pragma once

#include "writer-monad.hpp"
#include "../include/Pose.hpp"

Writer<Pose> move(double, const Pose &);
Writer<Pose> turn(degree_t, const Pose &);