#ifndef YADRO_TAPES_TAPE_EXTENDS_HPP
#define YADRO_TAPES_TAPE_EXTENDS_HPP

#include "tape.hpp"

#include <algorithm>
#include <array>
#include <memory>
#include <vector>

using Data = Tape::Data;

std::vector<Data> read_many(const std::unique_ptr<Tape>& tape, size_t steps);

void write_many(const std::unique_ptr<Tape>& tape, const std::vector<Data>& values);

void move_forward_many(const std::unique_ptr<Tape>& tape, size_t steps);

void reset(const std::unique_ptr<Tape>& tape);

template<size_t size>
void reset(const std::array<std::unique_ptr<Tape>, size>& tapes) {
  for (auto& tape: tapes) reset(tape);
}

void copy(const std::unique_ptr<Tape>& from, const std::unique_ptr<Tape>& to);

void copy_part(const std::unique_ptr<Tape>& from, const std::unique_ptr<Tape>& to, size_t part_size);

void sort(const std::unique_ptr<Tape>& from, const std::unique_ptr<Tape>& to, size_t block_size);

#endif// YADRO_TAPES_TAPE_EXTENDS_HPP
