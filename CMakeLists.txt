cmake_minimum_required(VERSION 3.10)
project(walking_leetcode)

set(CMAKE_CXX_STANDARD 20)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(ds_template include/Trie.cpp )

add_executable(walking_leetcode
        array/circular_array_loop.cpp
        )
target_link_libraries(walking_leetcode ds_template)