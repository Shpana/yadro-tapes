#ifndef YADRO_TAPES_ALGORITHM_HPP
#define YADRO_TAPES_ALGORITHM_HPP

#include "tapes/tape.hpp"

#include <memory>

class Algorithm {
public:
  Algorithm(std::unique_ptr<TapeStorage> &&input_tape,
            std::unique_ptr<TapeStorage> &&output_tape)
      : _input_tape(std::move(input_tape)), _output_tape(std::move(output_tape)) {}
  virtual void run() = 0;

protected:
  std::unique_ptr<TapeStorage> _input_tape;
  std::unique_ptr<TapeStorage> _output_tape;
};

#endif// YADRO_TAPES_ALGORITHM_HPP
