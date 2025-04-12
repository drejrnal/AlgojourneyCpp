#in this subdirectory, i want to add these executables corresponding to the source files
# what does these executables do?

file(GLOB_RECURSE SORT_GREEDY_SERIES_QA
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

foreach (source_file ${SORT_GREEDY_SERIES_QA})
    get_filename_component(executable_name ${source_file} NAME_WE)
    add_executable(${executable_name} ${source_file})
endforeach ()