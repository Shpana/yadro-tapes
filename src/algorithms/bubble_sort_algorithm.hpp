#ifndef YADRO_TAPES_BUBBLE_SORT_ALGORITHM_HPP
#define YADRO_TAPES_BUBBLE_SORT_ALGORITHM_HPP

#include "algorithm.hpp"
#include "copy_algorithm.hpp"
#include "tapes/file_based_tape.hpp"

class BubbleSortAlgorithm : public Algorithm<specs::EmptySpec> {
public:
  using Algorithm<specs::EmptySpec>::Algorithm;

  void run() override {
    size_t size = _input_tape->get_size();
    {
      auto temp_tape =
          std::make_unique<FileBasedTapeStorage>("../tests/tmp/temp.txt", size);
      CopyAlgorithm(std::move(_input_tape), std::move(temp_tape), {})
          .run();
    }
    {
      auto temp_tape =
          std::make_unique<FileBasedTapeStorage>("../tests/tmp/temp.txt", size);
      for (size_t i = 0; i < size - 1; ++i) {
        temp_tape->reset();
        for (size_t j = 0; j < size - i - 1; ++j) {
          auto lhs = temp_tape->read();
          temp_tape->move_forward();
          auto rhs = temp_tape->read();
          if (lhs > rhs) {
            temp_tape->write(lhs);
            temp_tape->move_back();
            temp_tape->write(rhs);
            temp_tape->move_forward();
          }
        }
      }
    }
    {
      auto temp_tape =
          std::make_unique<FileBasedTapeStorage>("../tests/tmp/temp.txt", size);
      CopyAlgorithm(std::move(temp_tape), std::move(_output_tape), {})
          .run();
    }
  }
};

#endif// YADRO_TAPES_BUBBLE_SORT_ALGORITHM_HPP
