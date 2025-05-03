include(FetchContent)
FetchContent_Declare(gtest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG 52eb8108c5bdec04579160ae17225d66034bd723 # release-1.17.0
)
FetchContent_MakeAvailable(gtest)

add_library(run_tests_lib src/utils/tapes.cpp
        src/utils/tapes.hpp)
target_include_directories(run_tests_lib PUBLIC ${CMAKE_SOURCE_DIR}/yadro_tapes)
target_link_libraries(run_tests_lib PUBLIC yadro_tapes_lib)
target_compile_definitions(run_tests_lib PRIVATE STATIC_FILES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/static")

add_executable(run_tests src/file_based_tape_tests.cpp)
target_include_directories(run_tests
        PUBLIC ${CMAKE_SOURCE_DIR}/yadro_tapes
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(run_tests PUBLIC run_tests_lib)
target_link_libraries(run_tests PUBLIC GTest::gtest_main)
