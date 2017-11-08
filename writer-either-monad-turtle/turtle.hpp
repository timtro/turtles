#pragma once

#include "../include/Pose.hpp"
#include "writer-either-monad.hpp"

enum class turtleError { hitWall, couldNotRotate };

template <typename T>
using EitherErrorOr = Either<T, turtleError>;

WriterWith<EitherErrorOr<Pose>> move(meter_t, const Pose &);
WriterWith<EitherErrorOr<Pose>> turn(degree_t, const Pose &);