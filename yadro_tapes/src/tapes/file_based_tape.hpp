#ifndef YADRO_TAPES_FILE_BASED_TAPE_HPP
#define YADRO_TAPES_FILE_BASED_TAPE_HPP

#include "tape.hpp"
#include "tapes/workloads/workload.hpp"

#include <filesystem>
#include <fstream>

class FileBasedTape : public Tape {
public:
  FileBasedTape(const std::filesystem::path& path, size_t tape_size);
  FileBasedTape(const std::filesystem::path& path, size_t tape_size,
                std::shared_ptr<Workload> workload);
  ~FileBasedTape() override;

  auto Read() -> Data override;
  auto Write(Data value) -> void override;
  auto MoveForward() -> void override;
  auto MoveBack() -> void override;
  [[nodiscard]] auto size() const -> size_t override { return tape_size_; }
  [[nodiscard]] auto head_position() const -> size_t override {
    return head_position_;
  }

private:
  std::fstream tape_file_;
  size_t tape_size_;
  size_t head_position_;
  std::shared_ptr<Workload> workload_;
};

#endif// YADRO_TAPES_FILE_BASED_TAPE_HPP