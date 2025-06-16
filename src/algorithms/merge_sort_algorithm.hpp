#ifndef YADRO_TAPES_MERGE_SORT_ALGORITHM_HPP
#define YADRO_TAPES_MERGE_SORT_ALGORITHM_HPP

#include "algorithm.hpp"
#include "tapes/tape_extends.hpp"

struct MemoryLimitSpec {
  size_t memory_limit;
};

class MergeSortAlgorithm : public Algorithm<2, MemoryLimitSpec> {
  struct Segment {
    size_t lhs, rhs;
  };

public:
  using Algorithm<2, MemoryLimitSpec>::Algorithm;

  auto Run() -> void override {
    size_t size = input_->size();

    if (size <= spec_.memory_limit) {
      Sort(input_, output_, size);
      return;
    }

    size_t leafs_count = 0;
    size_t remained = size;
    while (remained > 0) {
      size_t block_size = std::min(remained, spec_.memory_limit);
      Sort(input_, extra_[leafs_count % 2], block_size);
      remained -= block_size;
      leafs_count++;
    }
    Reset(extra_);

    size_t current_block_size = spec_.memory_limit;
    while (leafs_count > 1) {
      Reset(output_);
      Reset(extra_);

      remained = size;
      auto segment1 = Segment{0, 0}, segment2 = Segment{0, 0};
      while (remained > 0) {
        size_t block_size1 = std::min(remained, current_block_size);
        remained -= block_size1;
        if (remained == 0) {
          CopyPart(extra_[0], output_, block_size1);
          break;
        }
        size_t block_size2 = std::min(remained, current_block_size);
        remained -= block_size2;
        segment1 = Segment{segment1.rhs, segment1.rhs + block_size1};
        segment2 = Segment{segment2.rhs, segment2.rhs + block_size2};
        Merge(segment1, segment2);
        leafs_count--;
      }
      current_block_size *= 2;

      Reset(output_);
      Reset(extra_);

      remained = size;
      size_t new_leafs_count = 0;
      while (remained > 0) {
        size_t block_size = std::min(remained, current_block_size);
        remained -= block_size;
        CopyPart(output_, extra_[new_leafs_count % 2], block_size);
        new_leafs_count++;
      }
    }
  }

private:
  auto Merge(Segment segment1, Segment segment2) -> void {
    while (segment1.lhs < segment1.rhs && segment2.lhs < segment2.rhs) {
      auto u = extra_[0]->Read();
      auto v = extra_[1]->Read();
      if (u > v) {
        output_->Write(v);
        extra_[1]->MoveForward();
        segment2.lhs++;
      } else {
        output_->Write(u);
        extra_[0]->MoveForward();
        segment1.lhs++;
      }
      output_->MoveForward();
    }

    while (segment1.lhs < segment1.rhs) {
      auto value = extra_[0]->Read();
      output_->Write(value);
      output_->MoveForward();
      extra_[0]->MoveForward();
      segment1.lhs++;
    }
    while (segment2.lhs < segment2.rhs) {
      auto value = extra_[1]->Read();
      output_->Write(value);
      output_->MoveForward();
      extra_[1]->MoveForward();
      segment2.lhs++;
    }
  }
};

#endif// YADRO_TAPES_MERGE_SORT_ALGORITHM_HPP
