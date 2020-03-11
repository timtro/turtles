#pragma once

#include "../include/Pose.hpp"
#include "state-either-monad.hpp"

enum class turtleError { hitWall, couldNotRotate };

template <typename T>
using ErrorOr = std::variant<T, turtleError>;

template <typename T>
using StateWith = std::pair<T, Pose>;

StateWith<ErrorOr<meter_t>> move(meter_t, const Pose &);
StateWith<ErrorOr<degree_t>> turn(degree_t, const Pose &);
