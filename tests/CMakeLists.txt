cmake_minimum_required(VERSION 3.16)

project(stat_prob_tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

add_executable(sprinkler_test
    sprinkler_test.cpp
)
