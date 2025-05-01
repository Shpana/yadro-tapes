#ifndef YADRO_TAPES_BUBBLE_SORT_ALGORITHM_HPP
#define YADRO_TAPES_BUBBLE_SORT_ALGORITHM_HPP

#include "algorithm.hpp"

class BubbleSortAlgorithm : public Algorithm<specs::EmptySpec> {
public:
  using Algorithm<specs::EmptySpec>::Algorithm;

  void run() override {
    size_t size = _input_tape->get_size();

    for (size_t i = 0; i < size; ++i) {
      _output_tape->write(_input_tape->read());
      if (i == size - 1)
        break;
      _input_tape->move_forward();
      _output_tape->move_forward();
    }

    for (size_t i = 0; i < size - 1; ++i) {
      _reset(_output_tape);
      for (size_t j = 0; j < size - i - 1; ++j) {
        auto lhs = _output_tape->read();
        _output_tape->move_forward();
        auto rhs = _output_tape->read();
        if (lhs > rhs) {
          _output_tape->write(lhs);
          _output_tape->move_back();
          _output_tape->write(rhs);
          _output_tape->move_forward();
        }
      }
    }
  }

private:
  void _reset(const std::unique_ptr<TapeStorage>& tape) {
    while (tape->get_head_position() > 0)
      tape->move_back();
  }
};

#endif// YADRO_TAPES_BUBBLE_SORT_ALGORITHM_HPP
