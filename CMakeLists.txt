cmake_minimum_required(VERSION 3.10)
project(walking_leetcode)

set(CMAKE_CXX_STANDARD 20)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(ds_template
        include/Trie.cpp
        include/indexed_priority_queue.h
        include/NumTrie.h
        include/biIndexTree.h
        include/common.h
)

# as you can see, i have many directories and i want to add them all, and build this project
# how to configure this CMakeLists.txt file?
add_subdirectory(backtracking/)
add_subdirectory(array_string/)
#add_subdirectory(binary_tree/)
#add_subdirectory(dp/)
add_subdirectory(sort_greedy/)
add_subdirectory(stack_related)
#add_subdirectory(graph/)
# as we have had these subdirectories, then how to configure cmake file in each of them?
# i want to add all the cpp files in each directory, and build them all
#target_link_libraries(walking_leetcode ds_template)
