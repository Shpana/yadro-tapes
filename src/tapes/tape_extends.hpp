#ifndef YADRO_TAPES_TAPE_EXTENDS_HPP
#define YADRO_TAPES_TAPE_EXTENDS_HPP

#include "tape.hpp"

#include <array>
#include <memory>
#include <vector>

using Data = Tape::Data;

std::vector<Data> read_many(
    const std::unique_ptr<Tape>& tape,
    size_t steps) {
  std::vector<Data> result(static_cast<int>(steps), 0);
  for (size_t i = 0; i < steps; ++i) {
    result[i] = tape->read();
    tape->move_forward();
  }
  return result;
}

void write_many(
    const std::unique_ptr<Tape>& tape,
    const std::vector<Data>& values) {
  for (int value: values) {
    tape->write(value);
    tape->move_forward();
  }
}

void move_forward_many(
    const std::unique_ptr<Tape>& tape,
    size_t steps) {
  for (size_t i = 0; i < steps; ++i)
    tape->move_forward();
}

void reset(const std::unique_ptr<Tape>& tape) {
  while (tape->get_head_position() > 0)
    tape->move_back();
}

template<size_t size>
void reset(const std::array<std::unique_ptr<Tape>, size>& tapes) {
  for (auto& tape: tapes)
    reset(tape);
}

void copy(
    const std::unique_ptr<Tape>& from,
    const std::unique_ptr<Tape>& to) {
  reset(from);
  reset(to);
  for (size_t i = 0; i < from->get_size(); ++i) {
    to->write(from->read());
    from->move_forward();
    to->move_forward();
  }
}

#endif// YADRO_TAPES_TAPE_EXTENDS_HPP
