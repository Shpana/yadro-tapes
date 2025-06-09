#include "tape_extends.hpp"

#include <algorithm>

auto ReadMany(const TapePtr& tape, size_t steps) -> std::vector<Data> {
  std::vector<Data> result(static_cast<int>(steps), 0);
  for (size_t i = 0; i < steps; ++i) {
    result[i] = tape->Read();
    tape->MoveForward();
  }
  return result;
}

auto WriteMany(const TapePtr& tape, const std::vector<Data>& values) -> void {
  for (int value: values) {
    tape->Write(value);
    tape->MoveForward();
  }
}

auto Reset(const TapePtr& tape) -> void {
  while (tape->head_position() > 0)
    tape->MoveBack();
}

auto Sort(const TapePtr& from, const TapePtr& to, size_t block_size) -> void {
  auto buffer = ReadMany(from, block_size);
  std::sort(buffer.begin(), buffer.end());
  WriteMany(to, buffer);
}

auto Copy(const TapePtr& from, const TapePtr& to) -> void {
  Reset(from);
  Reset(to);
  for (size_t i = 0; i < from->size(); ++i) {
    to->Write(from->Read());
    from->MoveForward();
    to->MoveForward();
  }
}

auto CopyPart(const TapePtr& from, const TapePtr& to, size_t part_size) -> void {
  auto buffer = ReadMany(from, part_size);
  WriteMany(to, buffer);
}
