qt_add_library(preset STATIC
    preset.cpp
    preset_structures.h
)

target_link_libraries(preset PRIVATE
    Qt6::Core
    config
    glaze::glaze
)

target_include_directories(preset INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
