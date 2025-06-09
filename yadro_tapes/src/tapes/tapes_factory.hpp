#ifndef YADRO_TAPES_TAPES_FACTORY_HPP
#define YADRO_TAPES_TAPES_FACTORY_HPP

#include "file_based_tape.hpp"

using FileBasedTapePtr = std::unique_ptr<FileBasedTape>;

auto LoadTapeFromFile(
    const std::filesystem::path& filepath, size_t size) -> FileBasedTapePtr;
auto LoadTapeFromFile(
    const std::filesystem::path& filepath, size_t size, std::weak_ptr<Workload> workload)
    -> FileBasedTapePtr;

auto LoadTempTapeFromFile(
    const std::string& filename, size_t size) -> FileBasedTapePtr;
auto LoadTempTapeFromFile(
    const std::string& filename, size_t size, std::weak_ptr<Workload> workload)
    -> FileBasedTapePtr;

auto CreateTempTapeInFile(
    const std::string& filename, size_t size) -> FileBasedTapePtr;
auto CreateTempTapeInFile(
    const std::string& filename, size_t size, std::weak_ptr<Workload> workload)
    -> FileBasedTapePtr;

#endif// YADRO_TAPES_TAPES_FACTORY_HPP
