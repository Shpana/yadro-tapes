#include "file_based_tape.hpp"

FileBasedTape::FileBasedTape() {
}

FileBasedTape FileBasedTape::create(const FileBasedTapeSpec &spec, const std::filesystem::path &path) {
  return {};
}

int FileBasedTape::read() {
  return 0;
}

void FileBasedTape::write(int value) {
}

void FileBasedTape::move(Direction direction) {
}

void FileBasedTape::jump(size_t position) {
}
