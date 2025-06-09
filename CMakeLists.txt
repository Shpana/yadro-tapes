cmake_minimum_required(VERSION 3.28)
project(src)

set(CMAKE_CXX_STANDARD 17)

set(TMP_PATH "${CMAKE_SOURCE_DIR}/tmp")
set(CONFIGS_PATH "${CMAKE_SOURCE_DIR}/src")
set(STATIC_FILES_PATH "${CMAKE_SOURCE_DIR}/tests/static")

add_subdirectory(src)
add_subdirectory(tests)
