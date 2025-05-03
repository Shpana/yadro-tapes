#include "gtest/gtest.h"

#include "utils/static_tape_files.hpp"

TEST(file_based_tape_tests, creation) {
  ASSERT_NO_THROW(
      auto tape = load_static_tape("empty.dat", 0));
}

TEST(file_based_tape_tests, creation_file_not_found) {
  ASSERT_THROW(
      auto tape = load_static_tape("some_not_existing_file.dat", 0),
      std::runtime_error);
}

TEST(file_based_tape_tests, reading) {
  auto tape = load_static_tape("reading.dat", 1);
  ASSERT_EQ(tape->read(), 42);
}
