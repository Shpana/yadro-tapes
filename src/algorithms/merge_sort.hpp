#ifndef YADRO_TAPES_MERGE_SORT_HPP
#define YADRO_TAPES_MERGE_SORT_HPP

#include "tapes/file_based_tape.hpp"

#include <algorithm>
#include <vector>
#include <iostream>

using Data = TapeStorage::Data;

std::vector<Data> read_many(
    const std::unique_ptr<TapeStorage>& tape,
    size_t steps) {
  std::vector<Data> result(static_cast<int>(steps), 0);
  for (size_t i = 0; i < steps; ++i) {
    result[i] = tape->read();
    tape->move_forward();
  }
  return result;
}

void write_many(
    const std::unique_ptr<TapeStorage>& tape,
    const std::vector<Data>& values) {
  for (int value: values) {
    tape->write(value);
    tape->move_forward();
  }
}

void move_forward_many(
    const std::unique_ptr<TapeStorage>& tape,
    size_t steps) {
  for (size_t i = 0; i < steps; ++i)
    tape->move_forward();
}

void reset(const std::unique_ptr<TapeStorage>& tape) {
  while (tape->get_head_position() > 0)
    tape->move_back();
}

void copy(
    const std::unique_ptr<TapeStorage>& from,
    const std::unique_ptr<TapeStorage>& to) {
  reset(from);
  reset(to);
  for (size_t i = 0; i < from->get_size(); ++i) {
    to->write(from->read());
    from->move_forward();
    to->move_forward();
  }
}

class MergeSort {
public:
  MergeSort(std::unique_ptr<TapeStorage>&& input,
            std::unique_ptr<TapeStorage>&& output,
            std::unique_ptr<TapeStorage>&& extra,
            size_t memory_limit)
      : _input_tape(std::move(input)), _output_tape(std::move(output)), _extra_tape(std::move(extra)),
        _memory_limit(memory_limit) {}

  void run() {
    size_t leafs_count = 0;
    size_t remained = _input_tape->get_size();
    while (remained > 0) {
      auto block_size = std::min(remained, _memory_limit);
      auto block_buffer = read_many(_input_tape, block_size);
      std::sort(block_buffer.begin(), block_buffer.end());
      write_many(_extra_tape, block_buffer);
      leafs_count++;
      remained -= block_size;
    }

    size_t current_block_size = std::min(_input_tape->get_size(), _memory_limit);
    while (leafs_count > 1) {
      copy(_extra_tape, _output_tape);
      reset(_extra_tape);
      reset(_output_tape);

      size_t lhs = 0,
             mid = current_block_size,
             rhs = std::min(2 * current_block_size, _input_tape->get_size());
      while (mid < rhs) {
        move_forward_many(_output_tape, current_block_size);
        merge(lhs, mid, rhs);
        lhs = rhs;
        mid = std::min(mid + 2 * current_block_size, _input_tape->get_size());
        rhs = std::min(rhs + 2 * current_block_size, _input_tape->get_size());
        leafs_count--;
      }

      current_block_size *= 2;
    }

    copy(_extra_tape, _output_tape);
  }

  void merge(size_t lhs, size_t mid, size_t rhs) {
    size_t lhs_pointer = lhs,
           rhs_pointer = mid;
    while (lhs_pointer < mid && rhs_pointer < rhs) {
      auto u = _extra_tape->read();
      auto v = _output_tape->read();
      if (u > v) {
        _extra_tape->write(v);
        _output_tape->write(u);
        _output_tape->move_forward();
        rhs_pointer++;
      } else {
        _extra_tape->move_forward();
        lhs_pointer++;
      }
    }

    while (rhs_pointer > mid) {
      rhs_pointer--;
      _output_tape->move_back();
    }
    while (lhs_pointer < mid) {
      lhs_pointer++;
      _extra_tape->move_forward();
    }
    while (_extra_tape->get_head_position() < rhs) {
      auto u = _extra_tape->read();
      auto v = _output_tape->read();
      _extra_tape->write(v);
      _output_tape->write(u);
      _extra_tape->move_forward();
      _output_tape->move_forward();
    }
  }

private:
  std::unique_ptr<TapeStorage> _input_tape;
  std::unique_ptr<TapeStorage> _output_tape;
  std::unique_ptr<TapeStorage> _extra_tape;
  size_t _memory_limit;
};

#endif// YADRO_TAPES_MERGE_SORT_HPP
