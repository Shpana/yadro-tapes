#include "tapes_factory.hpp"

namespace {
#ifdef TMP_PATH
  std::filesystem::path tmp_path{TMP_PATH};
#else
  static_assert(false, "TMP_PATH is not specified!");
#endif
}// namespace

static auto CreateEmptyTempFile(const std::filesystem::path& filepath) -> void {
  std::filesystem::create_directories(tmp_path);
  std::fstream file;
  file.open(filepath, std::ios::out | std::ios::trunc);
  file.close();
}

auto LoadTapeFromFile(
    const std::filesystem::path& filepath, size_t size) -> FileBasedTapePtr {
  return std::make_unique<FileBasedTape>(filepath, size);
}

auto LoadTapeFromFile(
    const std::filesystem::path& filepath, size_t size, std::weak_ptr<Workload> workload)
    -> FileBasedTapePtr {
  auto tape = std::make_unique<FileBasedTape>(filepath, size);
  tape->AttachWorkload(std::move(workload));
  return tape;
}

auto LoadTempTapeFromFile(
    const std::string& filename, size_t size) -> FileBasedTapePtr {
  auto filepath = tmp_path / filename;
  return std::make_unique<FileBasedTape>(filepath, size);
}

auto LoadTempTapeFromFile(
    const std::string& filename, size_t size, std::weak_ptr<Workload> workload)
    -> FileBasedTapePtr {
  auto filepath = tmp_path / filename;
  auto tape = std::make_unique<FileBasedTape>(filepath, size);
  tape->AttachWorkload(std::move(workload));
  return tape;
}

auto CreateTempTapeInFile(
    const std::string& filename, size_t size) -> FileBasedTapePtr {
  auto filepath = tmp_path / filename;
  CreateEmptyTempFile(filepath);
  return std::make_unique<FileBasedTape>(filepath, size);
}

auto CreateTempTapeInFile(
    const std::string& filename, size_t size, std::weak_ptr<Workload> workload)
    -> FileBasedTapePtr {
  auto filepath = tmp_path / filename;
  CreateEmptyTempFile(filepath);
  auto tape = std::make_unique<FileBasedTape>(filepath, size);
  tape->AttachWorkload(std::move(workload));
  return tape;
}
