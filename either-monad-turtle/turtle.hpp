#pragma once

#include "../include/Pose.hpp"
#include "either-monad.hpp"

enum class turtleError { hitWall, couldNotRotate };

template <typename T>
using EitherErrorOr = Either<T, turtleError>;

EitherErrorOr<Pose> move(meter_t, const Pose &);
EitherErrorOr<Pose> turn(degree_t, const Pose &);