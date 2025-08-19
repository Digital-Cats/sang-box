cmake_minimum_required(VERSION 3.21)

project(sang-box VERSION 1.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Quick QuickControls2 LinguistTools)
qt_standard_project_setup()

set(QML_IMPORT_PATH ${CMAKE_BINARY_DIR}/qml_modules CACHE STRING "" FORCE)

include(FetchContent)

FetchContent_Declare(
  qml_material
  GIT_REPOSITORY https://github.com/hypengw/QmlMaterial.git
  GIT_TAG v0.1.3
  EXCLUDE_FROM_ALL)
FetchContent_MakeAvailable(qml_material)

add_subdirectory(src)

set(sang-box_sources
    src/main.cpp
    src/tray_icon.cpp
    src/config_list_model.cpp
    src/main_window.cpp
    src/settings_view_model.cpp
    src/underhood.cpp
)

qt_add_executable(sang-box
    ${sang-box_sources}
    resources/app.rc
    resources/sang-box.exe.manifest
)

qt_add_qml_module(sang-box
    URI SangBox
    VERSION 1.0
    QML_FILES
        src/Main.qml
        src/MainWindowView.qml
        src/ProfilesView.qml
        src/MainTab.qml
        src/SettingsTab.qml
        src/controls/AddNewProfileButton.qml
        src/controls/BasicTab.qml
        src/controls/ControlMenu.qml
        src/controls/DeleteProfileDialog.qml
        src/controls/LabeledCheckbox.qml
        src/controls/LinedHeader.qml
        src/controls/MenuButton.qml
        src/controls/PlayButton.qml
        src/controls/MDSwitch.qml
        src/controls/AddProfileDialog.qml
        src/controls/DialogButton.qml
        src/controls/ProfileContextMenu.qml
        QML_FILES src/controls/WelcomeDialog.qml
)

target_include_directories(sang-box PRIVATE
    include
)

target_link_libraries(sang-box PRIVATE
    Qt6::Widgets
    Qt6::Quick
    Qt6::QuickControls2
    qml_materialplugin
    config
    proxy
    settings
    utils
)

target_compile_definitions(sang-box PRIVATE QML_STATIC)

set_target_properties(sang-box PROPERTIES
    WIN32_EXECUTABLE ON
)

set(sang-box_resources
    "resources/fonts/LexendDeca-Regular.ttf"
    "resources/fonts/NotoSans-VariableFont_wdth,wght.ttf"
    "resources/images/app.ico"
    "resources/images/app_enable_proxy.ico"
    "resources/images/qt_logo.png"
    "resources/images/sang_logo.svg"
)

qt_add_resources(sang-box res
    PREFIX "/"
    BASE "resources"
    FILES
        ${sang-box_resources}
)

set(sang-box_langs
  languages/en_US.ts
)

file(GLOB_RECURSE TR_SOURCES "${CMAKE_SOURCE_DIR}/src/*")
qt_add_lupdate(sang-box TS_FILES ${sang-box_langs} SOURCES ${TR_SOURCES})

qt_add_lrelease(
    TS_FILES ${sang-box_langs}
)

qt_add_translations(sang-box
    TS_FILES
        ${sang-box_langs}
    LUPDATE_OPTIONS
        -no-obsolete
)

string(TIMESTAMP BUILD_TIME "%Y.%m.%d %H:%M")
add_definitions(-DPROJECT_VERSION="${PROJECT_VERSION}")
add_definitions(-DBUILD_TIME="${BUILD_TIME}")
add_definitions(-DCOMPILER_ID="${CMAKE_CXX_COMPILER_ID}")
add_definitions(-DCOMPILER_VERSION="${CMAKE_CXX_COMPILER_VERSION}")
add_definitions(-DSOURCE_ROOT="${CMAKE_SOURCE_DIR}")

install(TARGETS sang-box
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
