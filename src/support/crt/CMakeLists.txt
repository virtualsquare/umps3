set(CRT_FILES crtso crti)

set(CRT_CFLAGS -ffreestanding -ansi -Wall -c -mips1 -mabi=32 -mfp32 -mno-gpopt -G 0 -mno-abicalls -fno-pic)
set(CRT_CPPFLAGS -I${PROJECT_SOURCE_DIR}/src/include)

foreach(FILE ${CRT_FILES})
	add_custom_target(${FILE}.o ALL
		COMMAND ${XCGCC} ${CRT_CPPFLAGS} ${CRT_CFLAGS} -o
			${CMAKE_CURRENT_BINARY_DIR}/${FILE}.o ${FILE}.S
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

	set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
		${FILE}.o)

	install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${FILE}.o
		DESTINATION ${UMPS_LIB_DIR})

	install(FILES ${FILE}.S
		DESTINATION ${UMPS_DATA_DIR})
endforeach()
