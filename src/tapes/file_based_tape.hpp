#pragma once

#include "tape.hpp"
#include <chrono>
#include <filesystem>

using namespace std::chrono_literals;

struct FileBasedTapeSpec {
  std::chrono::milliseconds read_delay = 0ms;
  std::chrono::milliseconds write_delay = 0ms;
  std::chrono::milliseconds move_delay = 0ms;
  std::chrono::milliseconds jump_delay = 0ms;
};

class FileBasedTape : Tape {
public:
  static FileBasedTape create(const FileBasedTapeSpec &spec, const std::filesystem::path &path);
  int read() override;
  void write(int value) override;
  void move(Direction direction) override;
  void jump(size_t position) override;

private:
  FileBasedTape();

private:
  size_t _head_position = 0;
};
