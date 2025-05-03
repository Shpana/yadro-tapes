#ifndef YADRO_TAPES_TAPE_HPP
#define YADRO_TAPES_TAPE_HPP

#include <cstdint>
#include <cstddef>

class Tape {
public:
  using Data = int32_t;

public:
  virtual ~Tape() = default;

  virtual Data read() = 0;
  virtual void write(Data value) = 0;
  virtual void move_forward() = 0;
  virtual void move_back() = 0;
  [[nodiscard]] virtual size_t get_size() const = 0;
  [[nodiscard]] virtual size_t get_head_position() const = 0;
};

#endif// YADRO_TAPES_TAPE_HPP