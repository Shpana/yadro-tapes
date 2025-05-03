#ifndef YADRO_TAPES_TEMP_TAPE_FILES_HPP
#define YADRO_TAPES_TEMP_TAPE_FILES_HPP

#include "tapes/file_based_tape.hpp"

void create_empty_file(const std::filesystem::path& filepath);

std::unique_ptr<FileBasedTape> load_temp_tape(const std::string& filename, size_t size);
std::unique_ptr<FileBasedTape> load_temp_tape(
    const std::string& filename, size_t size, std::shared_ptr<Workload> workload);

std::unique_ptr<FileBasedTape> create_temp_tape(const std::string& filename, size_t size);
std::unique_ptr<FileBasedTape> create_temp_tape(
    const std::string& filename, size_t size, std::shared_ptr<Workload> workload);

#endif//YADRO_TAPES_TEMP_TAPE_FILES_HPP
