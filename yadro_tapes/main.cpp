#include "algorithms/merge_sort_algorithm.hpp"
#include "tapes/file_based_tape.hpp"
#include "tapes/workloads/sleeping_workload.hpp"
#include "utils/configs.hpp"

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
#ifdef CONFIGS_PATH
    auto workload = std::make_shared<SleepingWorkload>(
        load_sleeping_workload_spec(std::filesystem::path(CONFIGS_PATH) / "workloads.yaml"));
#else
    auto workload = std::make_shared<SleepingWorkload>(SleepingWorkloadSpec{});
#endif

#ifdef TMP_PATH
    auto tmp_path = std::filesystem::path(TMP_PATH);

    auto input_tape =
        std::make_unique<FileBasedTape>(input_file, tape_size, workload);
    auto output_tape =
        std::make_unique<FileBasedTape>(output_file, tape_size, workload);
    std::array<std::unique_ptr<Tape>, 2> extra_tapes = {
        std::make_unique<FileBasedTape>(tmp_path / "1.txt", tape_size, workload),
        std::make_unique<FileBasedTape>(tmp_path / "2.txt", tape_size, workload),
    };
    auto spec = MemoryLimitSpec(memory_limit);

    MergeSortAlgorithm(
        std::move(input_tape), std::move(output_tape), extra_tapes, spec)
        .run();
#else
    std::cerr << "Temp directory path is not provided!" << std::endl;
    return 1;
#endif
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
