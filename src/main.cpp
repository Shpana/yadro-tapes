#include "algorithms/algorithms_factory.hpp"

#include <filesystem>
#include <iostream>

auto main(int argc, char* argv[]) -> int {
  if (argc != 5) {
    std::cerr << "Usage: " << argv[0]
              << " <input_file> <output_file> <tape_size> <memory_limit>"
              << std::endl;
    return 1;
  }
  std::filesystem::path input_filepath = argv[1];
  std::filesystem::path output_filepath = argv[2];
  size_t tape_size = std::stoul(argv[3]);
  size_t memory_limit = std::stoul(argv[4]);

  auto algorithm =
      CreateMergeSortAlgorithm(
          std::move(input_filepath), std::move(output_filepath), tape_size, memory_limit);
  algorithm->Run();
}
