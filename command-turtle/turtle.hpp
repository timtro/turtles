#pragma once

#include "../include/nonconst-Pose.hpp"
#include "../include/tfunc/overload.hpp"

#include <numeric>
#include <variant>

struct TurtleMove {
  const meter_t distance;
};

struct TurtleTurn {
  const degree_t angle;
};

using TurtleCommand = std::variant<TurtleMove, TurtleTurn>;

Pose run(Pose, TurtleCommand);
Pose run_all(Pose, const std::vector<TurtleCommand> &);