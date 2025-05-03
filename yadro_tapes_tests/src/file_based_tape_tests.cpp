#include "gtest/gtest.h"

#include "utils/temp_tape_files.hpp"

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

TEST(file_based_tape_tests, writing) {
  auto tape = create_temp_tape("1.dat", 1);
  tape->write(24);
  ASSERT_EQ(tape->read(), 24);
  tape->write(42);
  ASSERT_EQ(tape->read(), 42);
}

TEST(file_based_tape_tests, moving) {
  auto tape = load_static_tape("100_inverse.dat", 100);
  ASSERT_EQ(tape->read(), 99);
  tape->move_forward();
  tape->move_forward();
  ASSERT_EQ(tape->read(), 97);
  tape->move_back();
  ASSERT_EQ(tape->read(), 98);
}