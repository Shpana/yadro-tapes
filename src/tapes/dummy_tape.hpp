#ifndef YADRO_TAPES_DUMMY_TAPE_HPP
#define YADRO_TAPES_DUMMY_TAPE_HPP

#include "tape.hpp"

class DummyTapeStorage : public TapeStorage {
public:
  Data read() override { return {}; }
  void write(TapeStorage::Data value) override {}
  void move_forward() override {}
  void move_back() override {}
  [[nodiscard]] size_t get_size() const override { return 0; }
  [[nodiscard]] size_t get_head_position() const override { return 0; }
};

#endif// YADRO_TAPES_DUMMY_TAPE_HPP
