#pragma once

#include <numeric>
#include <variant>
#include <vector>

#include "../include/nonconst-Pose.hpp"

struct TurtleMove {
  const meter_t distance;
};

struct TurtleTurn {
  const degree_t angle;
};

using TurtleCommand = std::variant<TurtleMove, TurtleTurn>;

Pose run(Pose, TurtleCommand);
Pose run_all(Pose, const std::vector<TurtleCommand> &);
