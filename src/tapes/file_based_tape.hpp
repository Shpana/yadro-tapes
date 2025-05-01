#ifndef YADRO_TAPES_FILE_BASED_TAPE_HPP
#define YADRO_TAPES_FILE_BASED_TAPE_HPP

#include "tape.hpp"

#include <filesystem>
#include <fstream>

class FileBasedTape : public Tape {
public:
  explicit FileBasedTape(const std::filesystem::path &path);
  ~FileBasedTape() override;

  int32_t read() override;
  void write(int32_t value) override;
  void move(Direction direction) override;
  bool can_move(Direction direction) override;
  size_t get_size() const override;

private:
  std::fstream _file;
  size_t _file_size = 0;

  int64_t _head_position = 0;
};

#endif// YADRO_TAPES_FILE_BASED_TAPE_HPP