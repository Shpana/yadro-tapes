#include "file_based_tape.hpp"

#include <iostream>

FileBasedTape::FileBasedTape(
    const std::filesystem::path& path, size_t tape_size)
    : _tape_size(tape_size), _head_position(0) {
  _tape_file.open(path, std::ios::in | std::ios::out | std::ios::binary);
  if (!_tape_file.is_open())
    throw std::runtime_error("Unable to open tape file!");
}

FileBasedTape::~FileBasedTape() {
  _tape_file.close();
}

Tape::Data FileBasedTape::read() {
  if (_head_position > _tape_size)
    throw std::out_of_range("Tape out of range!");
  Data value;
  _tape_file.seekg(
      static_cast<int64_t>(_head_position * sizeof(Data)), std::ios::beg);
  _tape_file.read(reinterpret_cast<char*>(&value), sizeof(Data));
  return value;
}

void FileBasedTape::write(Data value) {
  if (_head_position > _tape_size)
    throw std::out_of_range("Tape out of range!");
  _tape_file.seekp(
      static_cast<int64_t>(_head_position * sizeof(Data)), std::ios::beg);
  _tape_file.write(reinterpret_cast<char*>(&value), sizeof(Data));
}

void FileBasedTape::move_forward() {
  _head_position++;
}

void FileBasedTape::move_back() {
  _head_position--;
}
