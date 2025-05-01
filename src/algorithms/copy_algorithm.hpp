#ifndef YADRO_TAPES_COPY_ALGORITHM_HPP
#define YADRO_TAPES_COPY_ALGORITHM_HPP

#include "algorithm.hpp"

class CopyAlgorithm : public Algorithm {
public:
  CopyAlgorithm(std::unique_ptr<TapeStorage> &&input_tape,
                std::unique_ptr<TapeStorage> &&output_tape)
      : Algorithm(std::move(input_tape), std::move(output_tape)) {}

  void run() override {
    auto size = _input_tape->get_size();
    do {
      _output_tape->write(_input_tape->read());
      _input_tape->move_forward();
      _output_tape->move_forward();
    } while (_input_tape->get_head_position() < size);
  }
};

#endif// YADRO_TAPES_COPY_ALGORITHM_HPP
