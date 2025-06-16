include(FetchContent)
FetchContent_Declare(gtest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG 52eb8108c5bdec04579160ae17225d66034bd723 # release-1.17.0
)
FetchContent_MakeAvailable(gtest)

add_executable(yadro_tapes_tests
        file_based_tape_tests.cpp
        sorting_tests.cpp
)
target_include_directories(yadro_tapes_tests
        PUBLIC ${CMAKE_SOURCE_DIR}/src
)
target_link_libraries(yadro_tapes_tests
        PUBLIC yadro_tapes_lib
        PUBLIC GTest::gtest_main
)
target_compile_definitions(yadro_tapes_tests
        PRIVATE STATIC_FILES_PATH="${STATIC_FILES_PATH}"
)