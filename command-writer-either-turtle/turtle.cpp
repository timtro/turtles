#include "turtle.hpp"

#include <vector>

#include "../include/overload.hpp"
#include "../tfunc/include/function-operations.hpp"

using units::math::cos;
using units::math::sin;

constexpr bool exceptionalError{false};

// Same as writer-either-monad
M<Pose> move(meter_t r, const Pose &p0) {
  std::stringstream log;
  if (r > 100_m) {  // Enables us to provoke an error in the unit test.
    log << "hitWall\n";
    return {turtleError::hitWall, log.str()};
  } else {
    const auto dx = r * cos(p0.th);
    const auto dy = r * sin(p0.th);
    auto finalPose = Pose{p0.x + dx, p0.y + dy, p0.th};
    log << "moving from " << p0 << " to " << finalPose << '\n';
    return {finalPose, log.str()};
  }
}

// Same as writer-either-monad
M<Pose> turn(degree_t dth, const Pose &p0) {
  std::stringstream log;
  if (exceptionalError) {
    log << "couldNotRotate\n";
    return {turtleError::couldNotRotate, log.str()};
  } else {
    Pose finalPose = {p0.x, p0.y, degree_t{std::fmod((p0.th + dth)(), 360)}};
    log << "turning from " << p0 << " to " << finalPose << '\n';
    return {finalPose, log.str()};
  }
}
// cmove : double → Pose → (double, Pose)
const auto cmove = tf::curry(::move);
// cturn : degree_t → Pose → (degree_t, Pose)
const auto cturn = tf::curry(::turn);

M<Pose> run(M<Pose> mp0, TurtleCommand cmd) {
  auto handler = overload{
      [&mp0](TurtleMove mvcmd) { return mbind(mp0, cmove(mvcmd.distance)); },
      [&mp0](TurtleTurn tncmd) { return mbind(mp0, cturn(tncmd.angle)); }};
  return std::visit(handler, cmd);
}

M<Pose> run_all(Pose p0, const std::vector<TurtleCommand> &cmds) {
  return std::accumulate(cbegin(cmds), cend(cmds), make_writer_with_either(p0),
                         run);
}
