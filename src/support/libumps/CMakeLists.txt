set(UMPS_INCLUDE_DIR ${CMAKE_INSTALL_INCLUDEDIR}/umps2/umps)

install(FILES libumps.h types.h
        DESTINATION ${UMPS_INCLUDE_DIR})

install(CODE "execute_process(
                COMMAND rm -f libumps.e
                COMMAND ${CMAKE_COMMAND} -E create_symlink libumps.e libumps.h
                WORKING_DIRECTORY ${UMPS_INCLUDE_DIR})")

install(FILES libumps.S
        DESTINATION ${UMPS_DATA_DIR})
