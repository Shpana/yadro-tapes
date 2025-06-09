#ifndef YADRO_TAPES_TAPE_HPP
#define YADRO_TAPES_TAPE_HPP

#include <cstddef>
#include <cstdint>
#include <memory>

class Tape {
public:
  using Data = std::int32_t;

public:
  virtual ~Tape() = default;

  virtual auto Read() -> Data = 0;
  virtual auto Write(Data value) -> void = 0;
  virtual auto MoveForward() -> void = 0;
  virtual auto MoveBack() -> void = 0;
  [[nodiscard]] virtual auto size() const -> size_t = 0;
  [[nodiscard]] virtual auto head_position() const -> size_t = 0;
};

using TapePtr = std::unique_ptr<Tape>;

#endif// YADRO_TAPES_TAPE_HPP