set(ROM_TYPES coreboot exec)

foreach(TYPE ${ROM_TYPES})
        install(FILES ${TYPE}.S
                DESTINATION ${UMPS_DATA_DIR})
endforeach()

set(BIOS_CFLAGS -mips1 -mabi=32 -mno-abicalls -fno-pic -ffreestanding -mfp32)
set(BIOS_CPPFLAGS -I${PROJECT_SOURCE_DIR}/src/include)

foreach(TYPE ${ROM_TYPES})
        add_custom_target(${TYPE}.eb ALL
                COMMAND ${XCGCC} -c -EB ${BIOS_CPPFLAGS} ${BIOS_CFLAGS} -o
                        ${CMAKE_CURRENT_BINARY_DIR}/${TYPE}.eb ${TYPE}.S
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

        add_custom_target(${TYPE}.el ALL
                COMMAND ${XCGCC} -c -EL ${BIOS_CPPFLAGS} ${BIOS_CFLAGS} -o
                        ${CMAKE_CURRENT_BINARY_DIR}/${TYPE}.el ${TYPE}.S
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

        add_custom_target(${TYPE}.eb.rom.umps ALL
                COMMAND umps3-elf2umps -v -b ${TYPE}.eb
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
        add_dependencies(${TYPE}.eb.rom.umps ${TYPE}.eb umps3-elf2umps)

        add_custom_target(${TYPE}.el.rom.umps ALL
                COMMAND umps3-elf2umps -v -b ${TYPE}.el
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
        add_dependencies(${TYPE}.el.rom.umps ${TYPE}.el umps3-elf2umps)

        set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
                ${TYPE}.eb
                ${TYPE}.el
                ${TYPE}.eb.rom.umps
                ${TYPE}.el.rom.umps)
endforeach()

if(${WORDS_BIGENDIAN})
        set(ENDIAN eb)
else()
        set(ENDIAN el)
endif()

foreach(TYPE ${ROM_TYPES})
        install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${TYPE}.${ENDIAN}.rom.umps
                DESTINATION ${UMPS_DATA_DIR}
                RENAME ${TYPE}.rom.umps)
endforeach()
