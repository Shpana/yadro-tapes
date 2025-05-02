#include "algorithms/bubble_sort_algorithm.hpp"
#include "algorithms/merge_sort_algorithm.hpp"
#include "tapes/file_based_tape.hpp"

#include <filesystem>
#include <iostream>

int main() {
  std::filesystem::path root_path = "../tests/";
  size_t n, memory_limit;
  n = 20, memory_limit = 4;
  {

    auto input_tape =
        std::make_unique<FileBasedTape>(root_path / "input.txt", n);
    auto output_tape =
        std::make_unique<FileBasedTape>(root_path / "output.txt", n);
    auto extra_tape1 =
        std::make_unique<FileBasedTape>(root_path / "tmp/1.txt", n);
    auto extra_tape2 =
        std::make_unique<FileBasedTape>(root_path / "tmp/2.txt", n);

    //  MergeSortAlgorithm(std::move(input_tape), std::move(output_tape), std::move(extra_tape1), std::move(extra_tape2),
    //            memory_limit)
    //      .run();
    BubbleSortAlgorithm(std::move(input_tape), std::move(output_tape), {}).run();
  }
  {
    auto output_tape =
        std::make_unique<FileBasedTape>(root_path / "output.txt", n);

    for (size_t i = 0; i < n; ++i) {
      std::cout << output_tape->read() << " ";
      output_tape->move_forward();
    }
    std::cout << std::endl;
  }
}
