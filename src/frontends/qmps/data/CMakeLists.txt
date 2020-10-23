set(ID org.virtualsquare.umps3)

add_subdirectory(icons)

install(FILES ${ID}.desktop
        DESTINATION ${CMAKE_INSTALL_DATADIR}/applications)

install(FILES ${ID}.metainfo.xml
        DESTINATION ${CMAKE_INSTALL_DATADIR}/metainfo)
