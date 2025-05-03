#ifndef YADRO_TAPES_MERGE_SORT_ALGORITHM_HPP
#define YADRO_TAPES_MERGE_SORT_ALGORITHM_HPP

#include "algorithm.hpp"
#include "tapes/tape_extends.hpp"

struct MemoryLimitSpec {
  size_t memory_limit;

  MemoryLimitSpec(size_t limit)
      : memory_limit(limit) {}
};

class MergeSortAlgorithm : public Algorithm<2, MemoryLimitSpec> {
  struct Segment {
    size_t lhs, rhs;

    Segment(size_t _lhs, size_t _rhs)
      : lhs(_lhs), rhs(_rhs) {}
  };
public:
  using Algorithm<2, MemoryLimitSpec>::Algorithm;

  void run() override {
    size_t size = _input_tape->get_size();

    if (size <= _spec.memory_limit) {
      sort(_input_tape, _output_tape, size);
      return;
    }

    size_t leafs_count = 0;
    size_t remained = size;
    while (remained > 0) {
      size_t block_size = std::min(remained, _spec.memory_limit);
      sort(_input_tape, _extra_tapes[leafs_count % 2], block_size);
      remained -= block_size;
      leafs_count++;
    }
    reset(_extra_tapes);

    size_t current_block_size = _spec.memory_limit;
    while (leafs_count > 1) {
      reset(_output_tape);
      reset(_extra_tapes);

      remained = size;
      auto segment1 = Segment(0, 0),
           segment2 = Segment(0, 0);
      while (remained > 0) {
        size_t block_size1 = std::min(remained, current_block_size);
        remained -= block_size1;
        if (remained == 0) {
          copy_part(_extra_tapes[0], _output_tape, block_size1);
          break;
        }
        size_t block_size2 = std::min(remained, current_block_size);
        remained -= block_size2;
        segment1 = Segment(segment1.rhs, segment1.rhs + block_size1);
        segment2 = Segment(segment2.rhs, segment2.rhs + block_size2);
        _merge(segment1, segment2);
        leafs_count--;
      }
      current_block_size *= 2;

      reset(_output_tape);
      reset(_extra_tapes);

      remained = size;
      size_t new_leafs_count = 0;
      while (remained > 0) {
        size_t block_size = std::min(remained, current_block_size);
        remained -= block_size;
        copy_part(_output_tape, _extra_tapes[new_leafs_count % 2], block_size);
        new_leafs_count++;
      }
    }
  }

private:
  void _merge(Segment segment1, Segment segment2) {
    while (segment1.lhs < segment1.rhs &&
           segment2.lhs < segment2.rhs) {
      auto u = _extra_tapes[0]->read();
      auto v = _extra_tapes[1]->read();
      if (u > v) {
        _output_tape->write(v);
        _extra_tapes[1]->move_forward();
        segment2.lhs++;
      } else {
        _output_tape->write(u);
        _extra_tapes[0]->move_forward();
        segment1.lhs++;
      }
      _output_tape->move_forward();
    }

    while (segment1.lhs < segment1.rhs) {
      auto value = _extra_tapes[0]->read();
      _output_tape->write(value);
      _output_tape->move_forward();
      _extra_tapes[0]->move_forward();
      segment1.lhs++;
    }
    while (segment2.lhs < segment2.rhs) {
      auto value = _extra_tapes[1]->read();
      _output_tape->write(value);
      _output_tape->move_forward();
      _extra_tapes[1]->move_forward();
      segment2.lhs++;
    }
  }
};

#endif// YADRO_TAPES_MERGE_SORT_ALGORITHM_HPP
