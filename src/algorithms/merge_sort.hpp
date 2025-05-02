#ifndef YADRO_TAPES_MERGE_SORT_HPP
#define YADRO_TAPES_MERGE_SORT_HPP

#include "tapes/file_based_tape.hpp"
#include "tapes/tape_extends.hpp"

#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

class MergeSort {
public:
  MergeSort(std::unique_ptr<TapeStorage>&& input,
            std::unique_ptr<TapeStorage>&& output,
            std::unique_ptr<TapeStorage>&& extra1,
            std::unique_ptr<TapeStorage>&& extra2,
            size_t memory_limit)
      : _input_tape(std::move(input)),
        _output_tape(std::move(output)),
        _extra1_tape(std::move(extra1)),
        _extra2_tape(std::move(extra2)),
        _memory_limit(memory_limit) {
    _extra_tapes = {
        std::move(_extra1_tape),
        std::move(_extra2_tape)};
  }

  void run() {
    size_t leafs_count = 0;
    size_t remained = _input_tape->get_size();

    while (remained > 0) {
      auto block_size = std::min(_memory_limit, remained);
      auto block_buffer = read_many(_input_tape, block_size);
      std::sort(block_buffer.begin(), block_buffer.end());
      write_many(_extra_tapes[leafs_count % 2], block_buffer);
      leafs_count++;
      remained -= block_size;
    }

    size_t current_block_size = std::min(_memory_limit, _input_tape->get_size());
    while (leafs_count > 1) {
      size_t lhs1 = 0,
             rhs1 = current_block_size,
             lhs2 = 0,
             rhs2 = std::min(current_block_size, _input_tape->get_size() - rhs1);

      reset(_extra_tapes);
      reset(_output_tape);

      remained = _input_tape->get_size();
      while (remained > 0) {
        merge(lhs1, rhs1, lhs2, rhs2);
        lhs1 += current_block_size;
        rhs1 += std::min(current_block_size, remained);
        remained -= std::min(current_block_size, remained);
        lhs2 += current_block_size;
        rhs2 += std::min(current_block_size, remained);
        remained -= std::min(current_block_size, remained);
        leafs_count--;
      }
      current_block_size *= 2;

      reset(_extra_tapes);
      reset(_output_tape);
      for (size_t i = 0; i < leafs_count; ++i) {
        for (size_t j = 0; j < current_block_size; ++j) {
          auto value = _output_tape->read();
          _extra_tapes[i % 2]->write(value);
          _extra_tapes[i % 2]->move_forward();
          _output_tape->move_forward();
        }
      }
    }
  }

  void merge(size_t lhs1, size_t rhs1, size_t lhs2, size_t rhs2) {
    size_t ptr1 = lhs1,
           ptr2 = lhs2;
    while (ptr1 < rhs1 && ptr2 < rhs2) {
      auto u = _extra_tapes[0]->read();
      auto v = _extra_tapes[1]->read();
      if (u > v) {
        _output_tape->write(v);
        _extra_tapes[1]->move_forward();
        ptr2++;
      } else {
        _output_tape->write(u);
        _extra_tapes[0]->move_forward();
        ptr1++;
      }
      _output_tape->move_forward();
    }

    while (ptr1 < rhs1) {
      _output_tape->write(_extra_tapes[0]->read());
      _output_tape->move_forward();
      _extra_tapes[0]->move_forward();
      ptr1++;
    }
    while (ptr2 < rhs2) {
      _output_tape->write(_extra_tapes[1]->read());
      _output_tape->move_forward();
      _extra_tapes[1]->move_forward();
      ptr2++;
    }
  }

private:
  std::unique_ptr<TapeStorage> _input_tape;
  std::unique_ptr<TapeStorage> _output_tape;
  std::unique_ptr<TapeStorage> _extra1_tape;
  std::unique_ptr<TapeStorage> _extra2_tape;
  std::array<std::unique_ptr<TapeStorage>, 2> _extra_tapes;
  size_t _memory_limit;
};

#endif// YADRO_TAPES_MERGE_SORT_HPP
