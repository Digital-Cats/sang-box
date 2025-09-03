qt_add_library(config STATIC
    config.cpp
    config_manager.cpp
    config_io.cpp
    config_type.h
    config_data_handler.cpp
    remote_config.cpp
    config_downloader.cpp
    tools/config_obj.cpp
    tools/config_structures.h
)
target_link_libraries(config PRIVATE
    Qt6::Core
    Qt6::Network
    settings
    glaze::glaze
)
target_include_directories(config INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
