#pragma once

#include "../include/Pose.hpp"
#include "either-monad.hpp"

enum class turtleError { hitWall, couldNotRotate };

template <typename T>
using EitherErrorOr = std::variant<T, turtleError>;

EitherErrorOr<Pose> move(double, const Pose &);
EitherErrorOr<Pose> turn(degree_t, const Pose &);