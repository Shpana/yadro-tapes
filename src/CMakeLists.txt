include(FetchContent)
FetchContent_Declare(yaml-cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
)
FetchContent_MakeAvailable(yaml-cpp)

add_library(yadro_tapes_lib
        tapes/tape.hpp
        tapes/file_based_tape.hpp
        tapes/file_based_tape.cpp
        tapes/tape_extends.cpp
        tapes/tape_extends.hpp
        tapes/tapes_factory.cpp
        tapes/tapes_factory.hpp
        tapes/workloads/workload.hpp
        tapes/workloads/delaying_workload.hpp

        algorithms/algorithm.hpp
        algorithms/bubble_sort_algorithm.hpp
        algorithms/merge_sort_algorithm.hpp
        algorithms/algorithms_factory.cpp
        algorithms/algorithms_factory.hpp

        utils/configs.hpp
)
target_include_directories(yadro_tapes_lib
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(yadro_tapes_lib
        PUBLIC yaml-cpp::yaml-cpp
)
target_compile_definitions(yadro_tapes_lib
        PRIVATE TMP_PATH="${TMP_PATH}"
        PRIVATE CONFIGS_PATH="${CONFIGS_PATH}"
)

add_executable(yadro_tapes main.cpp)
target_include_directories(yadro_tapes
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(yadro_tapes
        PUBLIC yadro_tapes_lib
)
