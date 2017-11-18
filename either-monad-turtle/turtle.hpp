#pragma once

#include "../include/Pose.hpp"
#include "either-monad.hpp"

enum class turtleError { hitWall, couldNotRotate };

template <typename T>
using ErrorOr = MonadError<turtleError, T>;

ErrorOr<Pose> move(meter_t, const Pose &);
ErrorOr<Pose> turn(degree_t, const Pose &);