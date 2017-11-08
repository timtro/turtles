#pragma once

#include "../include/Pose.hpp"
#include "optional-monad.hpp"

std::optional<Pose> move(meter_t, const Pose &);
std::optional<Pose> turn(degree_t, const Pose &);