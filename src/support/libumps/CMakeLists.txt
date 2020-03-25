set(UMPS_INCLUDE_DIR ${CMAKE_INSTALL_INCLUDEDIR}/umps3/umps)

add_custom_target(libumps.e ALL
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/libumps.h
                ${CMAKE_CURRENT_BINARY_DIR}
        COMMAND ${CMAKE_COMMAND} -E create_symlink libumps.h libumps.e
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
        libumps.h libumps.e)

install(FILES libumps.h ${CMAKE_CURRENT_BINARY_DIR}/libumps.e types.h
        DESTINATION ${UMPS_INCLUDE_DIR})

install(FILES libumps.S
        DESTINATION ${UMPS_DATA_DIR})
