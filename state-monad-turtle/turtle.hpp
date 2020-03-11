#pragma once

#include "state-monad.hpp"

template <typename T>
using StateWith = std::pair<T, Pose>;

StateWith<meter_t> move(meter_t, const Pose &);
StateWith<degree_t> turn(degree_t, const Pose &);
