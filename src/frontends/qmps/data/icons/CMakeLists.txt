set(ICONS_DIR ${CMAKE_INSTALL_DATADIR}/icons/hicolor)

set(ICONS_SIZE 16x16 22x22 24x24 32x32 48x48 64x64)

foreach(SIZE ${ICONS_SIZE})
        install(FILES ${SIZE}/${ID}.svg
                DESTINATION ${ICONS_DIR}/${SIZE}/apps)
endforeach()
