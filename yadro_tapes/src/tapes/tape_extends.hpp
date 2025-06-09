#ifndef YADRO_TAPES_TAPE_EXTENDS_HPP
#define YADRO_TAPES_TAPE_EXTENDS_HPP

#include "tape.hpp"

#include <algorithm>
#include <array>
#include <memory>
#include <vector>

using Data = Tape::Data;

std::vector<Data> read_many(const std::unique_ptr<Tape>& tape, size_t steps) {
  std::vector<Data> result(static_cast<int>(steps), 0);
  for (size_t i = 0; i < steps; ++i) {
    result[i] = tape->Read();
    tape->MoveForward();
  }
  return result;
}

void write_many(const std::unique_ptr<Tape>& tape,
                const std::vector<Data>& values) {
  for (int value: values) {
    tape->Write(value);
    tape->MoveForward();
  }
}

void move_forward_many(const std::unique_ptr<Tape>& tape, size_t steps) {
  for (size_t i = 0; i < steps; ++i) tape->MoveForward();
}

void reset(const std::unique_ptr<Tape>& tape) {
  while (tape->head_position() > 0) tape->MoveBack();
}

template<size_t size>
void reset(const std::array<std::unique_ptr<Tape>, size>& tapes) {
  for (auto& tape: tapes) reset(tape);
}

void copy(const std::unique_ptr<Tape>& from, const std::unique_ptr<Tape>& to) {
  reset(from);
  reset(to);
  for (size_t i = 0; i < from->size(); ++i) {
    to->Write(from->Read());
    from->MoveForward();
    to->MoveForward();
  }
}

void copy_part(const std::unique_ptr<Tape>& from,
               const std::unique_ptr<Tape>& to, size_t part_size) {
  auto buffer = read_many(from, part_size);
  write_many(to, buffer);
}

void sort(const std::unique_ptr<Tape>& from, const std::unique_ptr<Tape>& to,
          size_t block_size) {
  auto buffer = read_many(from, block_size);
  std::sort(buffer.begin(), buffer.end());
  write_many(to, buffer);
}

#endif// YADRO_TAPES_TAPE_EXTENDS_HPP
