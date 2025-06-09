#ifndef YADRO_TAPES_TEMP_TAPE_FILES_HPP
#define YADRO_TAPES_TEMP_TAPE_FILES_HPP

#include "tapes/file_based_tape.hpp"

auto CreateEmptyFile(const std::filesystem::path& filepath) -> void;

auto LoadTempTapeFromFile(const std::string& filename,
                          size_t size) -> std::unique_ptr<FileBasedTape>;
auto LoadTempTapeFromFile(const std::string& filename, size_t size,
                          const std::shared_ptr<Workload>& workload)
    -> std::unique_ptr<FileBasedTape>;

auto CreateTempTapeInFile(const std::string& filename,
                          size_t size) -> std::unique_ptr<FileBasedTape>;
auto CreateTempTapeInFile(const std::string& filename, size_t size,
                          const std::shared_ptr<Workload>& workload)
    -> std::unique_ptr<FileBasedTape>;

#endif//YADRO_TAPES_TEMP_TAPE_FILES_HPP