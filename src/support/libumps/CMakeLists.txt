set(UMPS_INCLUDE_DIR ${CMAKE_INSTALL_INCLUDEDIR}/umps3/umps)

set(LIBUMPS_CFLAGS -ffreestanding -ansi -Wall -c -mips1 -mabi=32 -mfp32 -mno-gpopt -G 0 -mno-abicalls -fno-pic)
set(LIBUMPS_CPPFLAGS -I${PROJECT_SOURCE_DIR}/src/include)

add_custom_target(libumps.o ALL
	COMMAND ${XCGCC} ${LIBUMPS_CPPFLAGS} ${LIBUMPS_CFLAGS} -o
		${CMAKE_CURRENT_BINARY_DIR}/libumps.o libumps.S
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_custom_target(libumps.e ALL
	COMMAND ${CMAKE_COMMAND} -E copy
		${CMAKE_CURRENT_SOURCE_DIR}/libumps.h
		${CMAKE_CURRENT_BINARY_DIR}
	COMMAND ${CMAKE_COMMAND} -E create_symlink libumps.h libumps.e
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
	libumps.o libumps.h libumps.e)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libumps.o
	DESTINATION ${UMPS_LIB_DIR})

install(FILES libumps.h ${CMAKE_CURRENT_BINARY_DIR}/libumps.e const.h types.h
	DESTINATION ${UMPS_INCLUDE_DIR})

install(FILES libumps.S
	DESTINATION ${UMPS_DATA_DIR})
