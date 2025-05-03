#include "algorithms/merge_sort_algorithm.hpp"
#include "tapes/file_based_tape.hpp"
#include "tapes/workloads/sleeping_workload.hpp"

#include <filesystem>
#include <iostream>

int main(int argc, char* argv[]) {
  if (argc != 5) {
    std::cerr << "Usage: " << argv[0]
              << " <input_file> <output_file> <tape_size> <memory_limit>" << std::endl;
    return 1;
  }

  std::filesystem::path input_file = argv[1];
  std::filesystem::path output_file = argv[2];
  size_t tape_size = std::stoul(argv[3]);
  size_t memory_limit = std::stoul(argv[4]);
  {
    std::filesystem::path root = "../tests/";

    auto workload = std::make_shared<SleepingWorkload>(SleepingWorkloadSpec{});

    auto input_tape =
        std::make_unique<FileBasedTape>(input_file, tape_size, workload);
    auto output_tape =
        std::make_unique<FileBasedTape>(output_file, tape_size, workload);
    std::array<std::unique_ptr<Tape>, 2> extra_tapes = {
        std::make_unique<FileBasedTape>(root / "tmp/1.txt", tape_size, workload),
        std::make_unique<FileBasedTape>(root / "tmp/2.txt", tape_size, workload),
    };
    auto spec = MemoryLimitSpec(memory_limit);

    MergeSortAlgorithm(
        std::move(input_tape), std::move(output_tape), extra_tapes, spec)
        .run();
  }
  {
    auto output_tape =
        std::make_unique<FileBasedTape>(output_file, tape_size);
    for (size_t i = 0; i < tape_size; ++i) {
      std::cout << output_tape->read() << " ";
      output_tape->move_forward();
    }
    std::cout << std::endl;
  }
}
