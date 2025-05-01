#ifndef YADRO_TAPES_ALGORITHM_HPP
#define YADRO_TAPES_ALGORITHM_HPP

#include "tapes/tape.hpp"

#include <memory>

template<class TSpec>
class Algorithm {
public:
  Algorithm(std::unique_ptr<TapeStorage>&& input_tape,
            std::unique_ptr<TapeStorage>&& output_tape,
            const TSpec& spec)
      : _input_tape(std::move(input_tape)),
        _output_tape(std::move(output_tape)),
        _spec(spec) {}
  virtual void run() = 0;

protected:
  std::unique_ptr<TapeStorage> _input_tape;
  std::unique_ptr<TapeStorage> _output_tape;
  const TSpec& _spec;
};

namespace specs {
  struct EmptySpec {};

  struct MemorySpec {
    size_t memory_limit;
  };
}// namespace specs

#endif// YADRO_TAPES_ALGORITHM_HPP
