#ifndef YADRO_TAPES_TAPE_HPP
#define YADRO_TAPES_TAPE_HPP

#include <cstdint>

class Tape {
public:
  enum class Direction : int {
    Left = -1,
    Right = 1
  };

public:
  virtual ~Tape() = default;

  virtual int32_t read() = 0;
  virtual void write(int32_t value) = 0;
  virtual void move(Direction direction) = 0;
  virtual bool can_move(Direction direction) = 0;
  [[nodiscard]] virtual size_t get_size() const = 0;
};

#endif// YADRO_TAPES_TAPE_HPP