#ifndef YADRO_TAPES_COPY_ALGORITHM_HPP
#define YADRO_TAPES_COPY_ALGORITHM_HPP

#include "algorithm.hpp"

class CopyAlgorithm : public Algorithm<specs::EmptySpec> {
public:
  using Algorithm<specs::EmptySpec>::Algorithm;

  void run() override {
    while (_input_tape->get_head_position() < _input_tape->get_size()) {
      _output_tape->write(_input_tape->read());
      if (_input_tape->get_head_position() == _input_tape->get_size() - 1)
        break;
      _input_tape->move_forward();
      _output_tape->move_forward();
    }
  }
};

#endif// YADRO_TAPES_COPY_ALGORITHM_HPP
