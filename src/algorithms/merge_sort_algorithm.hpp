#ifndef YADRO_TAPES_MERGE_SORT_ALGORITHM_HPP
#define YADRO_TAPES_MERGE_SORT_ALGORITHM_HPP

#include "algorithm.hpp"
#include <algorithm>
#include <array>
#include <iostream>
#include <vector>


void copy(
    std::unique_ptr<TapeStorage>& from, std::unique_ptr<TapeStorage>& to) {
  ...;
}

class MergeSortAlgorithm : public Algorithm<specs::MemorySpec> {
public:
  MergeSortAlgorithm(std::unique_ptr<TapeStorage>&& input_tape,
                     std::unique_ptr<TapeStorage>&& output_tape,
                     const specs::MemorySpec& spec,
                     std::array<std::unique_ptr<TapeStorage>, 3>& working_tapes)
      : Algorithm<specs::MemorySpec>(std::move(input_tape), std::move(output_tape), spec),
        _working_tapes(working_tapes) {}

  void run() override {
    copy(_input_tape, _working_tapes[0]);
  }

  void merge_sort(int lhs, int rhs, int output_id) {
    if (rhs - lhs == _spec.memory_limit) {
      auto buffer = read_next(_input_tape, (int) _spec.memory_limit);
      std::sort(buffer.begin(), buffer.end());
      _working_tapes[output_id]->reset();
      _tapes_levels[output_id] = 1;
      for (auto elem: buffer) {
        _working_tapes[output_id]->write(elem);
        if (_working_tapes[output_id]->get_head_position() < _working_tapes[output_id]->get_size() - 1)
          _working_tapes[output_id]->move_forward();
      }
    } else {
      int mid = (lhs + rhs) / 2;
      merge_sort(lhs, mid, (output_id + 1) % 3);
      merge_sort(mid, rhs, (output_id + 2) % 3);
    }
  }

  void merge(int from1, int from2, int to) {
  }

  void precalc_levels(size_t size, size_t memory_limit) {
    int value = memory_limit;
    while (value < size) {
      _levels.push_back(value);
      value *= 2;
    }
    _levels.push_back(value);
    for (int elem: _levels)
      std::cout << elem << std::endl;
  }

private:
  std::vector<int> _levels;
  std::array<int, 3> _tapes_levels;
  std::array<std::unique_ptr<TapeStorage>, 3>& _working_tapes;
};

#endif// YADRO_TAPES_MERGE_SORT_ALGORITHM_HPP
