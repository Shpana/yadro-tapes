#include "file_based_tape.hpp"

#include <stdexcept>

FileBasedTape::FileBasedTape(const std::filesystem::path &path) {
  _file.open(path, std::ios::in | std::ios::out | std::ios::binary);

  _file.seekg(0, std::ios::end);
  _file_size = _file.tellg() / sizeof(int32_t);
  _file.seekg(0);
}

FileBasedTape::~FileBasedTape() {
  _file.close();
}

int32_t FileBasedTape::read() {
  if (_file.is_open()) {
    _file.seekg(static_cast<int64_t>(_head_position * sizeof(int32_t)));
    int32_t value;
    _file.read(reinterpret_cast<char *>(&value), sizeof(int32_t));
    return value;
  }
}

void FileBasedTape::write(int32_t value) {
  if (_file.is_open()) {
    _file.seekp(static_cast<int64_t>(_head_position * sizeof(int32_t)));
    _file.write(reinterpret_cast<char *>(&value), sizeof(int32_t));
  }
}

void FileBasedTape::move(Direction direction) {
  if (can_move(direction))
    throw std::out_of_range("Head position out of range!");
  _head_position += static_cast<int>(direction);
}

bool FileBasedTape::can_move(Tape::Direction direction) {
  int64_t new_position = _head_position + static_cast<int>(direction);
  return 0 <= new_position && new_position <= get_size();
}

size_t FileBasedTape::get_size() const {
  return _file_size;
}
