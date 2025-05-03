cmake_minimum_required(VERSION 3.28)
project(yadro_tapes)

set(CMAKE_CXX_STANDARD 17)

set(TMP_PATH "${CMAKE_SOURCE_DIR}/tmp")
set(CONFIGS_PATH "${CMAKE_SOURCE_DIR}/yadro_tapes/configs")
set(STATIC_FILES_PATH "${CMAKE_SOURCE_DIR}/yadro_tapes_tests/static")

add_subdirectory(yadro_tapes)
add_subdirectory(yadro_tapes_tests)
