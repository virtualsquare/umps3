cmake_minimum_required(VERSION 3.5)

project(umps
        VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-D_FORTIFY_SOURCE=2 -O2 -Wall -pedantic)

include(GNUInstallDirs)

include(TestBigEndian)
TEST_BIG_ENDIAN(WORDS_BIGENDIAN)
configure_file(config.h.in config.h)

# Check for MIPS cross toolchain
set(XT_PREFIXES ${MIPS_TOOL_PREFIX})
if(NOT XT_PREFIXES)
        set(XT_PREFIXES mips-sde-elf-)
        if(WORDS_BIGENDIAN)
                set(XT_PREFIXES mips-linux-gnu- mips-linux-
                        mips-elf- ${XT_PREFIXES})
        else()
                set(XT_PREFIXES mipsel-linux-gnu- mipsel-linux-
                        mipsel-elf- ${XT_PREFIXES})
        endif()
endif()

foreach(PREF ${XT_PREFIXES})
        find_program(XCGCC ${PREF}gcc)
        if(XCGCC)
                set(XT_PREFIX ${PREF})
                break()
        endif()
endforeach()

if(NOT XCGCC)
        message(FATAL_ERROR "MIPS toolchain (gcc) not found.")
endif()

find_program(XCAS ${PREF}as)
if(NOT XCAS)
        message(FATAL_ERROR "MIPS toolchain (as) not found.")
endif()

find_program(XCLD ${PREF}ld)
if(NOT XCLD)
        message(FATAL_ERROR "MIPS toolchain (ld) not found.")
endif()

# Checks for libelf
find_library(LIBELF elf)
if(NOT LIBELF)
        message(FATAL_ERROR "libelf not found.")
endif()

# Checks for libdl
find_library(LIBDL dl)
if(NOT LIBDL)
        message(FATAL_ERROR "libdl not found.")
endif()

include(FindPkgConfig)
pkg_check_modules(SIGCPP REQUIRED sigc++-2.0)

find_package(Boost 1.34 REQUIRED)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

if(${Qt5_VERSION_MINOR} LESS 11)
        execute_process(COMMAND git apply ${CMAKE_SOURCE_DIR}/patch/Qt5.patch
                        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
endif()

add_subdirectory(src)
add_subdirectory(man)

add_custom_target(uninstall ${CMAKE_COMMAND} -P
        "${PROJECT_SOURCE_DIR}/Uninstall.cmake")
