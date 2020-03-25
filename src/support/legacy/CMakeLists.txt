set(UMPS_LIB_DIR ${CMAKE_INSTALL_LIBDIR}/umps3)

set(LEGACY_LDSCRIPTS_EB elf32btsmip.h.umpsaout.x elf32btsmip.h.umpscore.x)
set(LEGACY_LDSCRIPTS_EL elf32ltsmip.h.umpsaout.x elf32ltsmip.h.umpscore.x)

if(${WORDS_BIGENDIAN})
        set(ENDIAN eb)
        set(LEGACY_LDSCRIPTS ${LEGACY_LDSCRIPTS_EB})
else()
        set(ENDIAN el)
        set(LEGACY_LDSCRIPTS ${LEGACY_LDSCRIPTS_EL})
endif()

foreach(FILE crtso crti libumps)
        install(FILES ${FILE}_pic.o.${ENDIAN}
                DESTINATION ${UMPS_LIB_DIR}
                RENAME ${FILE}.o)
endforeach()

install(FILES ${LEGACY_LDSCRIPTS}
        DESTINATION ${UMPS_DATA_DIR})
