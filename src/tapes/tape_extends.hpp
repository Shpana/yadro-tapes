#ifndef YADRO_TAPES_TAPE_EXTENDS_HPP
#define YADRO_TAPES_TAPE_EXTENDS_HPP

#include "tape.hpp"

#include <vector>

using Data = Tape::Data;

auto ReadMany(const TapePtr& tape, size_t steps) -> std::vector<Data>;
auto WriteMany(const TapePtr& tape, const std::vector<Data>& values) -> void;

auto Reset(const TapePtr& tape) -> void;

template<size_t size>
auto Reset(const std::array<TapePtr, size>& tapes) -> void {
  for (auto& tape: tapes)
    Reset(tape);
}

auto Sort(const TapePtr& from, const TapePtr& to, size_t block_size) -> void;

auto Copy(const TapePtr& from, const TapePtr& to) -> void;
auto CopyPart(const TapePtr& from, const TapePtr& to, size_t part_size) -> void;

#endif// YADRO_TAPES_TAPE_EXTENDS_HPP
