#include "temp_tape_files.hpp"

namespace {
#ifdef TMP_PATH
  std::filesystem::path tmp_path(TMP_PATH);
#endif
}

void create_empty_file(const std::filesystem::path& filepath) {
  std::fstream file;
  file.open(filepath, std::ios::out | std::ios::trunc);
  file.close();
}

std::unique_ptr<FileBasedTape> load_temp_tape(const std::string& filename, size_t size) {
  return load_temp_tape(filename, size, {});
}

std::unique_ptr<FileBasedTape> load_temp_tape(
    const std::string& filename, size_t size, std::shared_ptr<Workload> workload) {
  auto filepath = tmp_path / filename;
  return std::make_unique<FileBasedTape>(filepath, size, workload);
}

std::unique_ptr<FileBasedTape> create_temp_tape(const std::string& filename, size_t size) {
  return create_temp_tape(filename, size, {});
}

std::unique_ptr<FileBasedTape> create_temp_tape(
    const std::string& filename, size_t size, std::shared_ptr<Workload> workload) {
  auto filepath = tmp_path / filename;
  create_empty_file(filepath);
  return std::make_unique<FileBasedTape>(filepath, size, workload);
}
