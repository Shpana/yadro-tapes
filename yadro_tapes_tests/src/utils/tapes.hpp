#ifndef YADRO_TAPES_TAPES_HPP
#define YADRO_TAPES_TAPES_HPP

#include "tapes/file_based_tape.hpp"

FileBasedTape create_tape(const std::string& filename, size_t size);

#endif// YADRO_TAPES_TAPES_HPP
