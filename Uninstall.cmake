set(MANIFEST "${CMAKE_CURRENT_BINARY_DIR}/install_manifest.txt")

if(NOT EXISTS ${MANIFEST})
        message(FATAL_ERROR "Cannot find install manifest: '${MANIFEST}'")
endif()

file(STRINGS ${MANIFEST} files)
foreach(file ${files})
        if(EXISTS ${file} OR IS_SYMLINK ${file})
                message(STATUS "Removing file: '${file}'")

                execute_process(COMMAND rm "${file}"
                                OUTPUT_VARIABLE remove_file)

                if(${remove_file})
                        message(FATAL_ERROR
                                "Failed to remove file: '${file}'.")
                endif()
        else()
                MESSAGE(STATUS "File '${file}' does not exist.")
        endif()
endforeach(file)
