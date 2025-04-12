file(GLOB_RECURSE
        TEST_SOURCE_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

FOREACH (source_file ${TEST_SOURCE_FILES})
    get_filename_component(executable_name ${source_file} NAME_WE)
    add_executable(${executable_name} ${source_file})
ENDFOREACH ()