#ifndef YADRO_TAPES_BUBBLE_SORT_ALGORITHM_HPP
#define YADRO_TAPES_BUBBLE_SORT_ALGORITHM_HPP

#include "algorithm.hpp"
#include "tapes/tape_extends.hpp"

class BubbleSortAlgorithm : public Algorithm<specs::EmptySpec> {
public:
  using Algorithm<specs::EmptySpec>::Algorithm;

  void run() override {
    size_t size = _input_tape->get_size();

    copy(_input_tape, _output_tape);

    for (size_t i = 0; i < size - 1; ++i) {
      reset(_output_tape);
      for (size_t j = 0; j < size - i - 1; ++j) {
        auto u = _output_tape->read();
        _output_tape->move_forward();
        auto v = _output_tape->read();
        if (u > v) {
          _output_tape->write(u);
          _output_tape->move_back();
          _output_tape->write(v);
          _output_tape->move_forward();
        }
      }
    }
  }
};

#endif// YADRO_TAPES_BUBBLE_SORT_ALGORITHM_HPP
