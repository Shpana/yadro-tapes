#include "gtest/gtest.h"

#include "tapes/tape_extends.hpp"
#include "tapes/tapes_factory.hpp"
#include "algorithms/algorithms_factory.hpp"

namespace {
#ifdef STATIC_FILES_PATH
  std::filesystem::path static_files_path{STATIC_FILES_PATH};
#else
  static_assert(false, "STATIC_FILES_PATH is not specified!");
#endif
}// namespace

TEST(sorting_tests, bubble_sort) {
  size_t size = 100;
  {
    auto input_tape = LoadTapeFromFile(static_files_path / "100_inverse.dat", size);
    auto output_tape = CreateTempTapeInFile("output.dat", size);

    CreateBubbleSortAlgorithm(std::move(input_tape), std::move(output_tape))
        ->Run();
  }
  {
    auto tape = LoadTempTapeFromFile("output.dat", size);
    auto buffer = ReadMany(std::move(tape), size);

    std::vector<Tape::Data> expected_buffer(size, 0);
    for (size_t i = 0; i < size; ++i)
      expected_buffer[i] = static_cast<Tape::Data>(i);

    ASSERT_EQ(buffer, expected_buffer);
  }
}

TEST(sorting_tests, merge_sort) {
  size_t size = 100;
  size_t memory_limit = 6;
  {
    auto input_tape = LoadTapeFromFile(static_files_path / "100_inverse.dat", size);
    ASSERT_TRUE(input_tape);
    auto output_tape = CreateTempTapeInFile("output.dat", size);
    ASSERT_TRUE(output_tape);
    std::array<std::unique_ptr<Tape>, 2> extra_tapes = {
        CreateTempTapeInFile("1.dat", size),
        CreateTempTapeInFile("2.dat", size)
    };

    CreateMergeSortAlgorithm(
        std::move(input_tape), std::move(output_tape), std::move(extra_tapes), memory_limit)
        ->Run();
  }
  {
    std::unique_ptr<Tape> tape = LoadTempTapeFromFile("output.dat", size);
    auto buffer = ReadMany(tape, size);

    std::vector<Tape::Data> expected_buffer(size, 0);
    for (size_t i = 0; i < size; ++i)
      expected_buffer[i] = static_cast<Tape::Data>(i);

    ASSERT_EQ(buffer, expected_buffer);
  }
}

TEST(sorting_tests, merge_sort_little) {
  size_t size = 5;
  size_t memory_limit = 2;
  {
    auto input_tape = static_cast<TapePtr>(CreateTempTapeInFile("input.dat", size));
    auto output_tape = static_cast<TapePtr>(CreateTempTapeInFile("output.dat", size));
    std::array<std::unique_ptr<Tape>, 2> extra_tapes = {
        CreateTempTapeInFile("1.dat", size),
        CreateTempTapeInFile("2.dat", size)
    };

    std::vector<Tape::Data> values = {4, 2, 1, 3, 0};
    WriteMany(input_tape, values);
    Reset(input_tape);

    CreateMergeSortAlgorithm(
        std::move(input_tape), std::move(output_tape), std::move(extra_tapes), memory_limit)
        ->Run();
  }
  {
    std::unique_ptr<Tape> tape = LoadTempTapeFromFile("output.dat", size);
    auto buffer = ReadMany(tape, size);
    std::vector<Tape::Data> expected_buffer = {0, 1, 2, 3, 4};
    ASSERT_EQ(buffer, expected_buffer);
  }
}