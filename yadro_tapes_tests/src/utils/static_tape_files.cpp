#include "static_tape_files.hpp"

#include <filesystem>
#include <fstream>

namespace {
#ifdef STATIC_FILES_PATH
  std::filesystem::path static_files_path(STATIC_FILES_PATH);
#endif
}// namespace

std::unique_ptr<FileBasedTape> load_static_tape(const std::string& filename, size_t size) {
  return std::make_unique<FileBasedTape>(static_files_path / filename, size);
}
