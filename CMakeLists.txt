cmake_minimum_required(VERSION 3.14)

project(summation
    VERSION 1.0.0
    DESCRIPTION "Performance tests for summation"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(summer main.cpp)

include(FetchContent)

FetchContent_Declare(
    nanobench
    GIT_REPOSITORY https://github.com/martinus/nanobench
    GIT_TAG v4.3.11
)

FetchContent_MakeAvailable(nanobench)

target_link_libraries(summer nanobench::nanobench)
