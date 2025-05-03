#ifndef YADRO_TAPES_STATIC_TAPE_FILES_HPP
#define YADRO_TAPES_STATIC_TAPE_FILES_HPP

#include "tapes/file_based_tape.hpp"

std::unique_ptr<FileBasedTape> load_static_tape(const std::string& filename, size_t size);

#endif// YADRO_TAPES_STATIC_TAPE_FILES_HPP
