#include "algorithms/merge_sort.hpp"
#include "algorithms/print_algorithm.hpp"
#include "tapes/dummy_tape.hpp"
#include "tapes/file_based_tape.hpp"

#include <filesystem>
#include <iostream>

int main() {
  std::filesystem::path root_path = "../tests/";
  size_t n, memory_limit;
  n = 20, memory_limit = 4;

  {
    auto input_tape =
        std::make_unique<FileBasedTapeStorage>(root_path / "input.txt", n);
    auto output_tape =
        std::make_unique<FileBasedTapeStorage>(root_path / "output.txt", n);
    auto extra_tape1 =
        std::make_unique<FileBasedTapeStorage>(root_path / "tmp/1.txt", n);
    auto extra_tape2 =
        std::make_unique<FileBasedTapeStorage>(root_path / "tmp/2.txt", n);

    MergeSort(std::move(input_tape), std::move(output_tape), std::move(extra_tape1), std::move(extra_tape2),
              memory_limit)
        .run();
  }
  {
    auto extra1 =
        std::make_unique<FileBasedTapeStorage>(root_path / "tmp/1.txt", n);
    auto extra2 =
        std::make_unique<FileBasedTapeStorage>(root_path / "tmp/2.txt", n);
    auto input =
        std::make_unique<FileBasedTapeStorage>(root_path / "input.txt", n);
    auto output =
        std::make_unique<FileBasedTapeStorage>(root_path / "output.txt", n);

    PrintAlgorithm(std::move(extra1), std::make_unique<DummyTapeStorage>(), {})
        .run();
    PrintAlgorithm(std::move(extra2), std::make_unique<DummyTapeStorage>(), {})
        .run();
    PrintAlgorithm(std::move(input), std::make_unique<DummyTapeStorage>(), {})
        .run();
    PrintAlgorithm(std::move(output), std::make_unique<DummyTapeStorage>(), {})
        .run();
  }
}
