qt_add_library(utils STATIC
    html_color_text.cpp
)
target_link_libraries(utils PRIVATE Qt6::Gui Qt6::Core)
target_include_directories(utils INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
