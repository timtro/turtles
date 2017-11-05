#pragma once

#include "state-either-monad.hpp"

enum class turtleError { hitWall, couldNotRotate };

template <typename T>
using EitherErrorOr = std::variant<T, turtleError>;

template <typename T>
using StateWith = std::pair<T, Pose>;

StateWith<EitherErrorOr<double>> move(double, const Pose &);
StateWith<EitherErrorOr<degree_t>> turn(degree_t, const Pose &);