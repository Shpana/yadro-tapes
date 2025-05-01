cmake_minimum_required(VERSION 3.28)
project(yadro_tapes)

set(CMAKE_CXX_STANDARD 17)

include_directories(yadro_tapes src/)

add_executable(yadro_tapes src/main.cpp
        src/tapes/tape.hpp
        src/tapes/file_based_tape.hpp
        src/tapes/file_based_tape.cpp
        src/algorithms/algorithm.hpp
        src/algorithms/copy_algorithm.hpp
)
