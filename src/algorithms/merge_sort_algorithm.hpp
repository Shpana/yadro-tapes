#ifndef YADRO_TAPES_MERGE_SORT_ALGORITHM_HPP
#define YADRO_TAPES_MERGE_SORT_ALGORITHM_HPP

#include "algorithm.hpp"
#include "tapes/tape_extends.hpp"

struct MemoryLimitSpec {
  size_t memory_limit;

  MemoryLimitSpec(size_t limit)
      : memory_limit(limit) {}
};

class MergeSortAlgorithm : public Algorithm<2, MemoryLimitSpec> {
public:
  using Algorithm<2, MemoryLimitSpec>::Algorithm;

  void run() override {
  }
};

#endif// YADRO_TAPES_MERGE_SORT_ALGORITHM_HPP
