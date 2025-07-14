qt_add_library(config STATIC
    config.cpp
    config_editor.cpp
    config_editor.ui
    config_manager.cpp
    config_io.cpp
    config_type.h
    config_data_handler.cpp
)
target_link_libraries(config PRIVATE
    Qt6::Widgets
    settings
)
target_include_directories(config INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
