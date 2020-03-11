#pragma once

#include "../include/Pose.hpp"
#include "writer-either-monad.hpp"

enum class turtleError { hitWall, couldNotRotate };

template <typename T>
using ErrorOr = Either<T, turtleError>;

WriterWith<ErrorOr<Pose>> move(meter_t, const Pose &);
WriterWith<ErrorOr<Pose>> turn(degree_t, const Pose &);
