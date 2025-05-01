#pragma once

#include <cstddef>

class Tape {
public:
  virtual int read() = 0;
  virtual void write(int value) = 0;
  enum Direction : int {
    left = 0,
    right
  };
  virtual void move(Direction direction) = 0;
  virtual void jump(size_t position) = 0;
};
