#include "algorithms/merge_sort_algorithm.hpp"
#include "tapes/file_based_tape.hpp"
#include "tapes/workloads/delaying_workload.hpp"
#include "utils/configs.hpp"
#include "utils/temp_tape_files.hpp"

#include <filesystem>
#include <iostream>

auto main(int argc, char* argv[]) -> int {
  if (argc != 5) {
    std::cerr << "Usage: " << argv[0]
              << " <input_file> <output_file> <tape_size> <memory_limit>"
              << std::endl;
    return 1;
  }
  std::filesystem::path input_file = argv[1];
  std::filesystem::path output_file = argv[2];
  size_t tape_size = std::stoul(argv[3]);
  size_t memory_limit = std::stoul(argv[4]);

#ifdef CONFIGS_PATH
  auto workload = std::make_shared<DelayingWorkload>(LoadSleepingWorkloadSpec(
      std::filesystem::path(CONFIGS_PATH) / "workloads.yaml"));
#else
  auto workload = std::make_shared<SleepingWorkload>(SleepingWorkload::Spec{});
#endif

  auto input_tape =
      std::make_unique<FileBasedTape>(input_file, tape_size, workload);
  auto output_tape =
      std::make_unique<FileBasedTape>(output_file, tape_size, workload);
  std::array<std::unique_ptr<Tape>, 2> extra_tapes = {
      CreateTempTapeInFile("1.dat", tape_size, workload),
      CreateTempTapeInFile("2.dat", tape_size, workload),
  };
  auto spec = MemoryLimitSpec{memory_limit};

  auto algorithm = MergeSortAlgorithm(
      std::move(input_tape), std::move(output_tape), extra_tapes, spec);
  algorithm.Run();
}
