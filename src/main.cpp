#include "tapes/file_based_tape.hpp"
#include "algorithms/bubble_sort_algorithm.hpp"
#include "algorithms/print_algorithm.hpp"

int main() {
  BubbleSortAlgorithm(
      {},
      std::make_unique<FileBasedTapeStorage>("../tests/input.txt", 100),
      std::make_unique<FileBasedTapeStorage>("../tests/output.txt", 100)).run();

  PrintAlgorithm(
      {},
      std::make_unique<FileBasedTapeStorage>("../tests/input.txt", 100),
      std::make_unique<FileBasedTapeStorage>("../tests/input.txt", 100)).run();
  PrintAlgorithm(
      {},
      std::make_unique<FileBasedTapeStorage>("../tests/output.txt", 100),
      std::make_unique<FileBasedTapeStorage>("../tests/output.txt", 100)).run();
}
