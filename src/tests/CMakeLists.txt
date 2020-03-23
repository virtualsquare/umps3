add_executable(test_json_serialize test_json_serialize.cc)

add_dependencies(test_json_serialize base)

target_link_libraries(test_json_serialize base)

target_include_directories(test_json_serialize PRIVATE
        ${PROJECT_SOURCE_DIR}/src)
