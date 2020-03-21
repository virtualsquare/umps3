set(ROM_TYPES coreboot tapeboot exec)

foreach(TYPE ${ROM_TYPES})
        install(FILES ${TYPE}.S
                DESTINATION ${UMPS_DATA_DIR})
endforeach()

set(BIOS_CFLAGS -mips1 -mabi=32 -mno-abicalls -fno-pic -ffreestanding -mfp32)
set(BIOS_CPPFLAGS -I${PROJECT_SOURCE_DIR}/src/include)

foreach(TYPE ${ROM_TYPES})
        add_custom_target(${TYPE}.eb.rom.umps ALL
                COMMAND ${XCGCC} -c -EB ${BIOS_CPPFLAGS} ${BIOS_CFLAGS} -o
                        ${CMAKE_CURRENT_BINARY_DIR}/${TYPE}.eb
                        ${CMAKE_CURRENT_SOURCE_DIR}/${TYPE}.S
                COMMAND ${CMAKE_BINARY_DIR}/src/umps/umps2-elf2umps -v -b
                        ${CMAKE_CURRENT_BINARY_DIR}/${TYPE}.eb
                COMMAND rm -f ${CMAKE_CURRENT_BINARY_DIR}/${TYPE}.eb)
        add_dependencies(${TYPE}.eb.rom.umps umps2-elf2umps)

        add_custom_target(${TYPE}.el.rom.umps ALL
                COMMAND ${XCGCC} -c -EL ${BIOS_CPPFLAGS} ${BIOS_CFLAGS} -o
                        ${CMAKE_CURRENT_BINARY_DIR}/${TYPE}.el
                        ${CMAKE_CURRENT_SOURCE_DIR}/${TYPE}.S
                COMMAND ${CMAKE_BINARY_DIR}/src/umps/umps2-elf2umps -v -b
                        ${CMAKE_CURRENT_BINARY_DIR}/${TYPE}.el
                COMMAND rm -f ${CMAKE_CURRENT_BINARY_DIR}/${TYPE}.el)
        add_dependencies(${TYPE}.el.rom.umps umps2-elf2umps)
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
