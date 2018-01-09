#include "turtle.hpp"

#include <vector>

using units::math::cos;
using units::math::sin;

// run : (Pose, TurtleCommand) → Pose
Pose run(Pose p0, TurtleCommand cmd) {

  // Alternative which uses plain ISO C++ instead of overload:
  //
  // struct {
  //   Pose &p0;
  //   Pose operator()(TurtleMove cmd) {
  //     const auto dx = cmd.distance * cos(p0.th);
  //     const auto dy = cmd.distance * sin(p0.th);
  //     return Pose{p0.x + dx, p0.y + dy, p0.th};
  //   }
  //   Pose operator()(TurtleTurn cmd) {
  //     return Pose{p0.x, p0.y, degree_t{std::fmod((p0.th + cmd.angle)(),
  //     360)}};
  //   }
  // } handler{p0};

  auto handler = tf::overload(
      [&p0](TurtleMove mvcmd) -> Pose {
        const auto dx = mvcmd.distance * cos(p0.th);
        const auto dy = mvcmd.distance * sin(p0.th);
        return Pose{p0.x + dx, p0.y + dy, p0.th};
      },
      [&p0](TurtleTurn tncmd) -> Pose {
        return Pose{p0.x, p0.y,
                    degree_t{std::fmod((p0.th + tncmd.angle)(), 360)}};
      });

  return std::visit(handler, cmd);
}

// run_all : (Pose, [TurtleCommand]) → Pose
Pose run_all(Pose p0, const std::vector<TurtleCommand> &cmds) {
  return std::accumulate(cbegin(cmds), cend(cmds), p0, run);
}