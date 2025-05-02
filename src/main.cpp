#include "algorithms/bubble_sort_algorithm.hpp"
#include "algorithms/merge_sort_algorithm.hpp"
#include "tapes/file_based_tape.hpp"

#include <filesystem>
#include <iostream>

int main() {
  size_t size = 20, memory_limit = 4;

  std::filesystem::path root_path = "../tests/";
  {
    auto input_tape =
        std::make_unique<FileBasedTape>(root_path / "input.txt", size);
    auto output_tape =
        std::make_unique<FileBasedTape>(root_path / "output.txt", size);
    std::array<std::unique_ptr<Tape>, 2> extra_tapes = {
        std::make_unique<FileBasedTape>(root_path / "tmp/1.txt", size),
        std::make_unique<FileBasedTape>(root_path / "tmp/2.txt", size),
    };
    auto spec = MemoryLimitSpec(memory_limit);

    MergeSortAlgorithm(
        std::move(input_tape), std::move(output_tape), extra_tapes, spec)
        .run();
  }
  {
    auto output_tape =
        std::make_unique<FileBasedTape>(root_path / "output.txt", size);
    for (size_t i = 0; i < size; ++i) {
      std::cout << output_tape->read() << " ";
      output_tape->move_forward();
    }
    std::cout << std::endl;
  }
}
