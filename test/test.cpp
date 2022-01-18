#include <gtest/gtest.h>

#include <cstdlib>
#include <ctime>

// clang-format off
#include "datastructures.hpp"
#include "algorithms.hpp"
// clang-format on

int main(int argc, char **argv) {
  std::srand(unsigned(std::time(nullptr)));
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
