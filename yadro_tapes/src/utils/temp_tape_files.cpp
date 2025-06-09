#include "temp_tape_files.hpp"

#include <filesystem>

namespace {
#ifdef TMP_PATH
  std::filesystem::path tmp_path(TMP_PATH);
#endif
}// namespace

auto CreateEmptyFile(const std::filesystem::path& filepath) -> void {
  std::filesystem::create_directories(tmp_path);
  std::fstream file;
  file.open(filepath, std::ios::out | std::ios::trunc);
  file.close();
}

auto LoadTempTapeFromFile(const std::string& filename,
                          size_t size) -> std::unique_ptr<FileBasedTape> {
  return LoadTempTapeFromFile(filename, size, {});
}

auto LoadTempTapeFromFile(const std::string& filename, size_t size,
                          const std::shared_ptr<Workload>& workload)
    -> std::unique_ptr<FileBasedTape> {
  auto filepath = tmp_path / filename;
  return std::make_unique<FileBasedTape>(filepath, size, workload);
}

auto CreateTempTapeInFile(const std::string& filename,
                          size_t size) -> std::unique_ptr<FileBasedTape> {
  return CreateTempTapeInFile(filename, size, {});
}

auto CreateTempTapeInFile(const std::string& filename, size_t size,
                          const std::shared_ptr<Workload>& workload)
    -> std::unique_ptr<FileBasedTape> {
  auto filepath = tmp_path / filename;
  CreateEmptyFile(filepath);
  return std::make_unique<FileBasedTape>(filepath, size, workload);
}
