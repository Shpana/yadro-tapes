#ifndef YADRO_TAPES_BLOCK_SORT_ALGORITHM_HPP
#define YADRO_TAPES_BLOCK_SORT_ALGORITHM_HPP

#include "algorithm.hpp"

class BlockSortAlgorithm : public Algorithm<specs::MemorySpec> {
public:
  using Algorithm<specs::MemorySpec>::Algorithm;

  void run() override {
  }
};

#endif// YADRO_TAPES_BLOCK_SORT_ALGORITHM_HPP
