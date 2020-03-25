add_library(umps STATIC
        blockdev.h
        blockdev.cc
        blockdev_params.h
        const.h
        device.h
        device.cc
        disassemble.h
        disassemble.cc
        error.h
        event.h
        event.cc
        machine_config.h
        machine_config.cc
        machine.h
        machine.cc
        memspace.h
        memspace.cc
        mp_controller.h
        mp_controller.cc
        mpic.h
        mpic.cc
        processor.h
        processor.cc
        processor_defs.h
        stoppoint.h
        stoppoint.cc
        symbol_table.h
        symbol_table.cc
        systembus.h
        systembus.cc
        time_stamp.h
        time_stamp.cc
        types.h
        utility.h
        utility.cc
        vde_network.h
        vde_network.cc
        libvdeplug_dyn.h)

add_dependencies(umps base)

target_include_directories(umps PRIVATE
        ${PROJECT_BINARY_DIR}
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/src/include)

target_compile_options(umps PRIVATE ${SIGCPP_CFLAGS})
target_compile_definitions(umps PRIVATE -DPACKAGE_DATA_DIR="${UMPS_DATA_DIR}")
target_link_libraries(umps PRIVATE base)

add_executable(umps3-elf2umps elf2umps.cc)
target_include_directories(umps3-elf2umps PRIVATE
        ${PROJECT_BINARY_DIR}
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/src/include)
target_link_libraries(umps3-elf2umps ${LIBELF})

add_executable(umps3-mkdev mkdev.cc)
target_include_directories(umps3-mkdev PRIVATE
        ${PROJECT_BINARY_DIR}
        ${PROJECT_SOURCE_DIR}/src)

add_executable(umps3-objdump disassemble.cc objdump.cc)
target_include_directories(umps3-objdump PRIVATE
        ${PROJECT_BINARY_DIR}
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/src/include)

install(TARGETS umps3-elf2umps umps3-mkdev umps3-objdump
        RUNTIME
        DESTINATION ${CMAKE_INSTALL_BINDIR})
