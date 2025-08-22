qt_add_library(proxy STATIC
    proxy_manager.cpp
    windows_proxy.cpp
    core_updater.h core_updater.cpp
)
target_link_libraries(proxy PRIVATE
    Qt6::Widgets
    Qt6::Network
    wininet.lib
)
target_include_directories(proxy INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
