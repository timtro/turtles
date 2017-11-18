#pragma once

#include "../include/nonconst-Pose.hpp"
#include "../include/tfunc/overload.hpp"
#include "../writer-either-monad-turtle/writer-either-monad.hpp"

#include <numeric>
#include <variant>

enum class turtleError { hitWall, couldNotRotate };

template <typename T>
using ErrorOr = Either<T, turtleError>;

template <typename T>
using M = WriterWith<ErrorOr<T>>;

template <typename A>
auto make_writer_with_either(A a) {
  return mreturn<A, turtleError>(a);
}

struct TurtleMove {
  const meter_t distance;
};

struct TurtleTurn {
  const degree_t angle;
};

using TurtleCommand = std::variant<TurtleMove, TurtleTurn>;

M<Pose> run(M<Pose>, TurtleCommand);
M<Pose> run_all(Pose, const std::vector<TurtleCommand> &);