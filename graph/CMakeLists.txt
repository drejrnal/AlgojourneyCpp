# set(GRAPH_SOURCES_DIR graph)
# # what does ${CMAKE_CURRENT_SOURCE_DIR} mean? and what else does cmake reserve keywords like this?

# set(CURRENT_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
# set(GRAPH_SOURCES, [])
# message(STATUS "GRAPH SOURCES:${GRAPH_SOURCES}")
# message(STATUS ${CURRENT_SRC_DIR})
# message(STATUS ${CMAKE_CURRENT_BINARY_DIR})
# list(APPEND GRAPH_SOURCES
#         ${CURRENT_SRC_DIR}/grid_dfs.cpp
#         ${CURRENT_SRC_DIR}/shortest_path.cpp
#         ${CURRENT_SRC_DIR}/traffic_route.cpp
#         ${CURRENT_SRC_DIR}/word_ladder.cpp
#         #${CURRENT_SRC_DIR}/tarjan.cpp
#         ${CURRENT_SRC_DIR}/Topology.cpp
#         ${CURRENT_SRC_DIR}/redundant_connection.cpp
# )
# foreach (GRAPH_SOURCE ${GRAPH_SOURCES})
#     get_filename_component(GRAPH_SOURCE_NAME ${GRAPH_SOURCE} NAME_WE)
#     add_executable(${GRAPH_SOURCE_NAME} ${GRAPH_SOURCE})
# endforeach ()

file(GLOB_RECURSE GRAPH_SERIES_QA
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

FOREACH (source_file ${GRAPH_SERIES_QA})
    get_filename_component(executable_name ${source_file} NAME_WE)
    add_executable(${executable_name} ${source_file})
ENDFOREACH ()