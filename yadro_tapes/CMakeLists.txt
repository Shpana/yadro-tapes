include(FetchContent)
FetchContent_Declare(yaml-cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
)
FetchContent_MakeAvailable(yaml-cpp)

add_library(yadro_tapes_lib src/tapes/tape.hpp
        src/tapes/file_based_tape.hpp
        src/tapes/file_based_tape.cpp
        src/tapes/tape_extends.hpp
        src/tapes/workloads/workload.hpp
        src/tapes/workloads/delaying_workload.hpp
        src/algorithms/algorithm.hpp
        src/algorithms/bubble_sort_algorithm.hpp
        src/algorithms/merge_sort_algorithm.hpp
        src/utils/configs.hpp
        src/utils/temp_tape_files.hpp
        src/utils/temp_tape_files.cpp
)
target_include_directories(yadro_tapes_lib
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src
)
target_link_libraries(yadro_tapes_lib
        PUBLIC yaml-cpp::yaml-cpp
)
target_compile_definitions(yadro_tapes_lib
        PRIVATE TMP_PATH="${TMP_PATH}"
)

add_executable(yadro_tapes main.cpp)
target_include_directories(yadro_tapes
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src
)
target_link_libraries(yadro_tapes
        PUBLIC yadro_tapes_lib
)
target_compile_definitions(yadro_tapes
        PRIVATE CONFIGS_PATH="${CONFIGS_PATH}"
)
