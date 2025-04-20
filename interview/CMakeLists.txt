FILE(GLOB_RECURSE INTERVIEW_SERIES_QA
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

FOREACH (source_file ${INTERVIEW_SERIES_QA})
    get_filename_component(executable_name ${source_file} NAME_WE)
    message(STATUS "file name:${executable_name}")
    add_executable(${executable_name} ${source_file})
ENDFOREACH ()