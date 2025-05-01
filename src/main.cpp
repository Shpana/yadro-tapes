#include "algorithms/copy_algorithm.hpp"
#include "tapes/file_based_tape.hpp"

int main() {
  auto algorithm = CopyAlgorithm(
      std::make_unique<FileBasedTapeStorage>("C:/Dev/input.txt"),
      std::make_unique<FileBasedTapeStorage>("C:/Dev/output.txt")
      );
  algorithm.run();
}
