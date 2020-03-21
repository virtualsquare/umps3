add_library(base STATIC json.cc trackable_mixin.cc)
target_include_directories(base PRIVATE ${PROJECT_SOURCE_DIR}/src)
target_compile_options(base PRIVATE ${SIGCPP_CFLAGS})
