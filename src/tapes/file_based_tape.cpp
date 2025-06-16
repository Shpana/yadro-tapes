#include "file_based_tape.hpp"

FileBasedTape::FileBasedTape(const std::filesystem::path& path, size_t tape_size)
    : tape_size_(tape_size), head_position_(0) {
  tape_file_.open(path, std::ios::in | std::ios::out | std::ios::binary);
  if (!tape_file_.is_open())
    throw std::runtime_error("Unable to open tape file!");
}

FileBasedTape::~FileBasedTape() { tape_file_.close(); }

auto FileBasedTape::Read() -> Tape::Data {
  if (head_position_ > tape_size_)
    throw std::out_of_range("Tape out of range!");
  Data value;
  tape_file_.seekg(static_cast<int64_t>(head_position_ * sizeof(Data)), std::ios::beg);
  tape_file_.read(reinterpret_cast<char*>(&value), sizeof(Data));
  if (!workload_.expired()) {
    workload_.lock()->TriggerRead();
  }
  return value;
}

auto FileBasedTape::Write(Data value) -> void {
  if (head_position_ > tape_size_)
    throw std::out_of_range("Tape out of range!");
  tape_file_.seekp(static_cast<int64_t>(head_position_ * sizeof(Data)), std::ios::beg);
  tape_file_.write(reinterpret_cast<char*>(&value), sizeof(Data));
  if (!workload_.expired()) {
    workload_.lock()->TriggerWrite();
  }
}

auto FileBasedTape::MoveForward() -> void {
  head_position_++;
  if (!workload_.expired()) {
    workload_.lock()->TriggerMovement();
  }
}

auto FileBasedTape::MoveBack() -> void {
  head_position_--;
  if (!workload_.expired()) {
    workload_.lock()->TriggerMovement();
  }
}
