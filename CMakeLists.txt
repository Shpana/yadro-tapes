cmake_minimum_required(VERSION 3.28)
project(yadro_tapes)

set(CMAKE_CXX_STANDARD 17)

include_directories(yadro_tapes src/)

add_executable(yadro_tapes src/main.cpp
        src/tapes/tape.hpp
        src/tapes/file_based_tape.hpp
        src/tapes/file_based_tape.cpp
        src/algorithms/algorithm.hpp
        src/algorithms/bubble_sort_algorithm.hpp
        src/algorithms/merge_sort_algorithm.hpp
        src/tapes/tape_extends.hpp
        src/tapes/workloads/workload.hpp
        src/tapes/workloads/sleeping_workload.hpp
        src/utils/configs.hpp
)

include(FetchContent)

FetchContent_Declare(yaml-cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
)
FetchContent_MakeAvailable(yaml-cpp)

target_link_libraries(yadro_tapes PUBLIC yaml-cpp::yaml-cpp)

