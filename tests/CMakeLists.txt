cmake_minimum_required(VERSION 3.16)

project(sprinkler_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(sprinkler_test
    sprinkler_test.cpp
)

target_include_directories(sprinkler_test PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)