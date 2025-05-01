#ifndef YADRO_TAPES_BUBBLE_SORT_ALGORITHM_HPP
#define YADRO_TAPES_BUBBLE_SORT_ALGORITHM_HPP

#include "algorithm.hpp"

#include <iostream>

class BubbleSortAlgorithm : Algorithm {
public:
  BubbleSortAlgorithm(std::unique_ptr<Tape> &&input_tape,
                      std::unique_ptr<Tape> &&output_tape)
      : Algorithm(std::move(input_tape), std::move(output_tape)) {}

  void run() override {
    std::cout << _input_tape->read() << std::endl;
    _output_tape->write(200);
    std::cout << _output_tape->read() << std::endl;
  }
};

#endif// YADRO_TAPES_BUBBLE_SORT_ALGORITHM_HPP
