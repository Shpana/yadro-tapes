#include "algorithms_factory.hpp"

#include "tapes/tapes_factory.hpp"
#include "tapes/workloads/delaying_workload.hpp"
#include "utils/configs.hpp"

auto CreateBubbleSortAlgorithm(
    std::filesystem::path&& input_filepath,
    std::filesystem::path&& output_filepath, std::size_t size)
    -> std::unique_ptr<BubbleSortAlgorithm> {
#ifdef CONFIGS_PATH
  auto workload = std::make_shared<DelayingWorkload>(
      LoadSleepingWorkloadSpec(std::filesystem::path{CONFIGS_PATH} / "workloads.yaml"));

  auto input_tape = LoadTapeFromFile(input_filepath, size, workload);
  auto output_tape = LoadTapeFromFile(output_filepath, size, workload);
#else
  auto input_tape = LoadTapeFromFile(input_filepath, size);
  auto output_tape = LoadTapeFromFile(output_filepath, size);
#endif
  return std::make_unique<BubbleSortAlgorithm>(std::move(input_tape), std::move(output_tape));
}

auto CreateBubbleSortAlgorithm(
    TapePtr&& input_tape,
    TapePtr&& output_tape)
    -> std::unique_ptr<BubbleSortAlgorithm> {
  return std::make_unique<BubbleSortAlgorithm>(std::move(input_tape), std::move(output_tape));
}

auto CreateMergeSortAlgorithm(
    std::filesystem::path&& input_filepath,
    std::filesystem::path&& output_filepath,
    std::size_t size, std::size_t memory_limit)
    -> std::unique_ptr<MergeSortAlgorithm> {
#ifdef CONFIGS_PATH
  auto workload = std::make_shared<DelayingWorkload>(
      LoadSleepingWorkloadSpec(std::filesystem::path{CONFIGS_PATH} / "workloads.yaml"));

  auto input_tape = LoadTapeFromFile(input_filepath, size, workload);
  auto output_tape = LoadTapeFromFile(output_filepath, size, workload);
  std::array<TapePtr, 2> extra_tapes = {
      CreateTempTapeInFile("1.dat", size, workload),
      CreateTempTapeInFile("2.dat", size, workload),
  };
#else
  auto input_tape = LoadTapeFromFile(input_filepath, size);
  auto output_tape = LoadTapeFromFile(output_filepath, size);
  std::array<TapePtr, 2> extra_tapes = {
      CreateTempTapeInFile("1.dat", size),
      CreateTempTapeInFile("2.dat", size),
  };
#endif
  auto spec = MemoryLimitSpec{memory_limit};
  return std::make_unique<MergeSortAlgorithm>(
      std::move(input_tape), std::move(output_tape), std::move(extra_tapes), std::move(spec));
}

auto CreateMergeSortAlgorithm(
    TapePtr&& input_tape,
    TapePtr&& output_tape,
    std::array<TapePtr, 2>&& extra_tapes,
    std::size_t memory_limit)
    -> std::unique_ptr<MergeSortAlgorithm> {
  auto spec = MemoryLimitSpec{memory_limit};
  return std::make_unique<MergeSortAlgorithm>(
      std::move(input_tape), std::move(output_tape), std::move(extra_tapes), std::move(spec));
}
