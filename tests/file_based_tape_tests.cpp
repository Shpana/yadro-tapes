#include "gtest/gtest.h"

#include "tapes/tapes_factory.hpp"

namespace {
#ifdef STATIC_FILES_PATH
  std::filesystem::path static_files_path{STATIC_FILES_PATH};
#else
  static_assert(false, "STATIC_FILES_PATH is not specified!");
#endif
}// namespace

TEST(file_based_tape_tests, creation) {
  ASSERT_NO_THROW(
      auto tape = LoadTapeFromFile(static_files_path / "empty.dat", 0));
}

TEST(file_based_tape_tests, creation_file_not_found) {
  ASSERT_THROW(
      auto tape = LoadTapeFromFile(static_files_path / "some_not_existing_file.dat", 0),
      std::runtime_error);
}

TEST(file_based_tape_tests, reading) {
  auto tape = LoadTapeFromFile(static_files_path / "reading.dat", 1);
  ASSERT_EQ(tape->Read(), 42);
}

TEST(file_based_tape_tests, writing) {
  auto tape = CreateTempTapeInFile("1.dat", 1);
  tape->Write(24);
  ASSERT_EQ(tape->Read(), 24);
  tape->Write(42);
  ASSERT_EQ(tape->Read(), 42);
}

TEST(file_based_tape_tests, moving) {
  auto tape = LoadTapeFromFile(static_files_path / "100_inverse.dat", 100);
  ASSERT_EQ(tape->Read(), 99);
  tape->MoveForward();
  tape->MoveForward();
  ASSERT_EQ(tape->Read(), 97);
  tape->MoveBack();
  ASSERT_EQ(tape->Read(), 98);
}