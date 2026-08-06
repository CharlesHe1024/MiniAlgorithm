cmake_minimum_required(VERSION 3.20)
project(MiniAlgorithms LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

add_library(
        minialgo
        INTERFACE
)
target_include_directories(
        minialgo
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Demo
add_executable(
        app
        app/main.cpp
)
target_link_libraries(
        app
        PRIVATE
        minialgo
)

# Tests
add_executable(
        test_utility
        tests/test_utility.cpp
)
target_link_libraries(
        test_utility
        PRIVATE
        minialgo
)
add_test(
        NAME test_utility
        COMMAND test_utility
)