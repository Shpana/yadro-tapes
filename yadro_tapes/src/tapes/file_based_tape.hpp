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

  Data read() override;
  void write(Data value) override;
  void move_forward() override;
  void move_back() override;
  [[nodiscard]] size_t get_size() const override { return _tape_size; }
  [[nodiscard]] size_t get_head_position() const override { return _head_position; }

private:
  std::fstream _tape_file;
  size_t _tape_size;
  size_t _head_position;
  std::shared_ptr<Workload> _workload;
};

#endif// YADRO_TAPES_FILE_BASED_TAPE_HPP