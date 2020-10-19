add_subdirectory(icons)

install(FILES umps3.desktop
        DESTINATION ${CMAKE_INSTALL_DATADIR}/applications)

install(FILES org.virtualsquare.umps3.metainfo.xml
        DESTINATION ${CMAKE_INSTALL_DATADIR}/metainfo)
