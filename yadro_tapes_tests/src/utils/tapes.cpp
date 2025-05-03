#include "tapes.hpp"

#include <filesystem>

namespace {
#ifdef STATIC_FILES_PATH
  std::filesystem::path static_files_path(STATIC_FILES_PATH);
#endif
}// namespace

FileBasedTape create_tape(const std::string& filename, size_t size) {
  return {static_files_path / filename, size};
}