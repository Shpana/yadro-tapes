#ifndef YADRO_TAPES_PRINT_ALGORITHM_HPP
#define YADRO_TAPES_PRINT_ALGORITHM_HPP

#include "algorithm.hpp"

#include <iostream>

class PrintAlgorithm : public Algorithm<specs::EmptySpec> {
public:
  using Algorithm<specs::EmptySpec>::Algorithm;

  void run() override {
    size_t size = _input_tape->get_size();
    for (size_t i = 0; i < size; ++i) {
      std::cout << _input_tape->read() << " ";
      if (i == size - 1)
        break;
      _input_tape->move_forward();
    }
    std::cout << std::endl;
  }
};

#endif// YADRO_TAPES_PRINT_ALGORITHM_HPP
