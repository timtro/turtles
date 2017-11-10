#pragma once

#include <limits>

namespace test_fixtures {

  constexpr auto delta = std::numeric_limits<double>::epsilon() * 100;

  constexpr char manualLog[] = {
      "moving from [0 m, 0 m, 0 rad] to [10 m, 0 m, 0 rad]\n"
      "turning from [10 m, 0 m, 0 rad] to [10 m, 0 m, 2.0944 rad]\n"
      "moving from [10 m, 0 m, 2.0944 rad] to [5 m, 8.66025 m, 2.0944 rad]\n"
      "turning from [5 m, 8.66025 m, 2.0944 rad] to [5 m, 8.66025 m, 4.18879 "
      "rad]\n"
      "moving from [5 m, 8.66025 m, 4.18879 rad] to [-2.66454e-15 m, "
      "3.55271e-15 m, 4.18879 rad]\n"
      "turning from [-2.66454e-15 m, 3.55271e-15 m, 4.18879 rad] to "
      "[-2.66454e-15 m, 3.55271e-15 m, 0 rad]\n"};

  const char manualLogWithErr[] = {
      "moving from [0 m, 0 m, 0 rad] to [10 m, 0 m, 0 rad]\n"
      "turning from [10 m, 0 m, 0 rad] to [10 m, 0 m, 2.0944 rad]\n"
      "hitWall\n"};

} // namespace test_fixtures