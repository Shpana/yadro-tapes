#ifndef YADRO_TAPES_ALGORITHM_HPP
#define YADRO_TAPES_ALGORITHM_HPP

#include "tapes/tape.hpp"

#include <memory>

template<size_t extra_tapes_number, class TSpec>
class Algorithm {
public:
  Algorithm(std::unique_ptr<Tape>&& input_tape, std::unique_ptr<Tape>&& output_tape,
            const std::array<std::unique_ptr<Tape>, extra_tapes_number>& extra_tapes = {},
            const TSpec& spec = {})
      : _input_tape(std::move(input_tape)), _output_tape(std::move(output_tape)), _extra_tapes(extra_tapes), _spec(spec) {}
  virtual void run() = 0;

protected:
  std::unique_ptr<Tape> _input_tape;
  std::unique_ptr<Tape> _output_tape;
  const std::array<std::unique_ptr<Tape>, extra_tapes_number>& _extra_tapes;
  const TSpec& _spec;
};

#endif// YADRO_TAPES_ALGORITHM_HPP
