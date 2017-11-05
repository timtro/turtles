#pragma once

#include <limits>

namespace test_fixtures {

  constexpr auto delta = std::numeric_limits<double>::epsilon() * 100;

  constexpr char manualLog[] = {
      "moving from [0, 0, 0 rad] to [10, 0, 0 rad]\n"
      "turning from [10, 0, 0 rad] to [10, 0, 2.0944 rad]\n"
      "moving from [10, 0, 2.0944 rad] to [5, 8.66025, 2.0944 rad]\n"
      "turning from [5, 8.66025, 2.0944 rad] to [5, 8.66025, 4.18879 rad]\n"
      "moving from [5, 8.66025, 4.18879 rad] to [-2.66454e-15, 3.55271e-15, "
      "4.18879 rad]\n"
      "turning from [-2.66454e-15, 3.55271e-15, 4.18879 rad] to [-2.66454e-15, "
      "3.55271e-15, 0 rad]\n"};

} // namespace test_fixtures