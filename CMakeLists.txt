cmake_minimum_required(VERSION 3.16)
project(pause_hammer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/lib)

add_definitions(-DUNICODE -D_UNICODE)

add_subdirectory(eo_pause_hammer/src)
enable_testing()