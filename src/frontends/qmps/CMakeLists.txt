add_subdirectory(data)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
find_package(Qt4 REQUIRED)

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

add_executable(umps2
        qmps.qrc
        main.cc
        application.h
        application.cc
        debug_session.h
        debug_session.cc
        monitor_window.h
        monitor_window_priv.h
        monitor_window.cc
        error_hooks.cc
        create_machine_dialog.h
        create_machine_dialog.cc
        stop_mask_view.h
        stop_mask_view.cc
        processor_list_model.h
        processor_list_model.cc
        machine_config_dialog.h
        machine_config_dialog_priv.h
        machine_config_dialog.cc
        machine_config_view.h
        machine_config_view.cc
        trace_browser.h
        trace_browser_priv.h
        trace_browser.cc
        memory_view_delegate.h
        hex_view.h
        hex_view_priv.h
        hex_view.cc
        symbol_table_model.h
        symbol_table_model.cc
        processor_window.h
        processor_window.cc
        code_view.h
        code_view_priv.h
        code_view.cc
        register_set_snapshot.h
        register_set_snapshot.cc
        register_set_widget.h
        register_set_widget.cc
        tlb_model.h
        tlb_model.cc
        terminal_view.h
        terminal_view.cc
        terminal_window.h
        terminal_window_priv.h
        terminal_window.cc
        cpu_status_map.h
        cpu_status_map.cc
        stoppoint_list_model.h
        stoppoint_list_model.cc
        suspect_type_delegate.h
        suspect_type_delegate.cc
        device_tree_view.h
        device_tree_view.cc
        device_tree_model.h
        device_tree_model.cc
        add_breakpoint_dialog.h
        add_breakpoint_dialog.cc
        add_suspect_dialog.h
        add_suspect_dialog.cc
        add_tracepoint_dialog.h
        add_tracepoint_dialog.cc
        address_line_edit.h
        address_line_edit.cc
        mac_id_edit.h
        mac_id_edit.cc
        boolean_item_delegate.h
        boolean_item_delegate.cc
        register_item_delegate.h
        register_item_delegate.cc
        ui_utils.h
        ui_utils.cc
        tree_view.h
        tree_view.cc
        flat_push_button.h
        flat_push_button.cc)

target_include_directories(umps2
        PRIVATE
        ${PROJECT_BINARY_DIR}
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/src/frontends
        ${PROJECT_SOURCE_DIR}/src/include)

set(QT_DEFINES -DQT_NO_DEBUG -DQT_NO_KEYWORDS -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED)
target_compile_options(umps2 PRIVATE ${QT_DEFINES} ${SIGCPP_CFLAGS})

add_dependencies(umps2 base umps)

target_compile_definitions(umps2 PRIVATE -DPACKAGE_VERSION="${PACKAGE_VERSION}")

target_link_libraries(umps2
        PRIVATE
        base
        umps
        ${QT_LIBRARIES}
        ${SIGCPP_LIBRARIES}
        ${LIBDL})

install(TARGETS umps2
        RUNTIME
        DESTINATION ${CMAKE_INSTALL_BINDIR})
