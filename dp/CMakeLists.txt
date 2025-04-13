file(GLOB_RECURSE
        SORT_GREEDY_SERIES_QA
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

FOREACH (source_file ${SORT_GREEDY_SERIES_QA})
    get_filename_component(executable_name ${source_file} NAME_WE)
    add_executable(${executable_name} ${source_file})
ENDFOREACH ()