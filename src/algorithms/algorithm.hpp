#ifndef YADRO_TAPES_ALGORITHM_HPP
#define YADRO_TAPES_ALGORITHM_HPP

#include "../tapes/tape.hpp"

#include <array>

template<size_t extra_tapes_count, typename TSpec>
class Algorithm {
  using ExtraTapes = std::array<TapePtr, extra_tapes_count>;

public:
  Algorithm(TapePtr&& input, TapePtr&& output,
            ExtraTapes&& extra = {}, TSpec&& spec = {})
      : input_(std::move(input)), output_(std::move(output)),
        extra_(std::move(extra)), spec_(std::move(spec)) {}
  virtual ~Algorithm() = default;
  virtual auto Run() -> void = 0;

protected:
  TapePtr input_;
  TapePtr output_;
  ExtraTapes extra_;
  TSpec spec_;
};

#endif// YADRO_TAPES_ALGORITHM_HPP
