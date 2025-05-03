#include "gtest/gtest.h"

#include "algorithms/bubble_sort_algorithm.hpp"
#include "algorithms/merge_sort_algorithm.hpp"
#include "tapes/tape_extends.hpp"
#include "utils/temp_tape_files.hpp"

#include "utils/static_tape_files.hpp"

TEST(sorting_tests, bubble_sort) {
  size_t size = 100;
  {
    auto input_tape = load_static_tape("100_inverse.dat", size);
    auto output_tape = create_temp_tape("output.dat", size);
    BubbleSortAlgorithm(std::move(input_tape), std::move(output_tape))
        .run();
  }
  {
    auto tape = load_temp_tape("output.dat", size);
    auto buffer = read_many(std::move(tape), size);

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
    auto input_tape = load_static_tape("100_inverse.dat", size);
    auto output_tape = create_temp_tape("output.dat", size);
    std::array<std::unique_ptr<Tape>, 2> extra_tapes = {
        create_temp_tape("1.dat", size),
        create_temp_tape("2.dat", size)};
    auto specs = MemoryLimitSpec(memory_limit);

    MergeSortAlgorithm(std::move(input_tape), std::move(output_tape), extra_tapes, specs)
        .run();
  }
  {
    auto tape = load_temp_tape("output.dat", size);
    auto buffer = read_many(std::move(tape), size);

    std::vector<Tape::Data> expected_buffer(size, 0);
    for (size_t i = 0; i < size; ++i)
      expected_buffer[i] = static_cast<Tape::Data>(i);

    ASSERT_EQ(buffer, expected_buffer);
  }
}