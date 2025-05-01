#include "algorithms/bubble_sort_algorithm.hpp"
#include "tapes/file_based_tape.hpp"

int main() {
  auto algorithm = BubbleSortAlgorithm(
      std::make_unique<FileBasedTape>("C:/Dev/input.txt"),
      std::make_unique<FileBasedTape>("C:/Dev/output.txt"));
  algorithm.run();
}
