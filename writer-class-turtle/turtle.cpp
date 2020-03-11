#include "turtle.hpp"

using units::math::cos;
using units::math::sin;

Writer<Pose> move(meter_t r, const Pose &p0) {
  WriterBuilder<Pose> moved;
  const auto dx = r * cos(p0.th);
  const auto dy = r * sin(p0.th);
  moved.value = Pose{p0.x + dx, p0.y + dy, p0.th};
  moved.log << "moving from " << p0 << " to " << moved.value << '\n';
  return moved.build();
}

Writer<Pose> turn(degree_t dth, const Pose &p0) {
  WriterBuilder<Pose> turned;
  turned.value = {p0.x, p0.y, degree_t{std::fmod((p0.th + dth)(), 360)}};
  turned.log << "turning from " << p0 << " to " << turned.value << '\n';
  return turned.build();
}
