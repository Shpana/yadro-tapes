#include "file_based_tape.hpp"

#include <iostream>

FileBasedTapeStorage::FileBasedTapeStorage(
    const std::filesystem::path& path, size_t tape_size)
    : _tape_size(tape_size) {
  _tape_file.open(path, std::ios::in | std::ios::out | std::ios::binary);
  if (!_tape_file.is_open())
    throw std::runtime_error("Unable to open tape file!");
}

FileBasedTapeStorage::~FileBasedTapeStorage() {
  _tape_file.close();
}

TapeStorage::Data FileBasedTapeStorage::read() {
  Data value;
  _tape_file.seekg(
      static_cast<int64_t>(_head_position * sizeof(Data)), std::ios::beg);
  _tape_file.read(reinterpret_cast<char*>(&value), sizeof(Data));
  return value;
}

void FileBasedTapeStorage::write(Data value) {
  _tape_file.seekp(
      static_cast<int64_t>(_head_position * sizeof(Data)), std::ios::beg);
  _tape_file.write(reinterpret_cast<char*>(&value), sizeof(Data));
}

void FileBasedTapeStorage::move_forward() {
  if (_head_position >= _tape_size - 1) {
    std::cout << _head_position << std::endl;
    throw std::out_of_range("Tape out of range!");
  }
  _head_position++;
}

void FileBasedTapeStorage::move_back() {
  if (_head_position == 0)
    throw std::out_of_range("Tape out of range!");
  _head_position--;
}
