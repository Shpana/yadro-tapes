#ifndef YADRO_TAPES_BUBBLE_SORT_ALGORITHM_HPP
#define YADRO_TAPES_BUBBLE_SORT_ALGORITHM_HPP

#include "algorithm.hpp"
#include "tapes/tape_extends.hpp"

struct EmptySpec {};

class BubbleSortAlgorithm : public Algorithm<0, EmptySpec> {
public:
  using Algorithm<0, EmptySpec>::Algorithm;

  auto Run() -> void override {
    size_t size = input_->size();

    Copy(input_, output_);

    for (size_t i = 0; i < size - 1; ++i) {
      Reset(output_);
      for (size_t j = 0; j < size - i - 1; ++j) {
        auto u = output_->Read();
        output_->MoveForward();
        auto v = output_->Read();
        if (u > v) {
          output_->Write(u);
          output_->MoveBack();
          output_->Write(v);
          output_->MoveForward();
        }
      }
    }
  }
};

#endif// YADRO_TAPES_BUBBLE_SORT_ALGORITHM_HPP
