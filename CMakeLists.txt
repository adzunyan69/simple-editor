cmake_minimum_required(VERSION 3.5)

project(Editor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
set(PROJECT_SOURCES
        main.cpp
        editorwindow.cpp
        editorwindow.h
        editorwindow.ui

        custom_objects/custom_object.h
        custom_objects/object_reader.h
        custom_objects/json_object_reader.h
        custom_objects/json_object_reader.cpp
        custom_objects/object_writer.h
        custom_objects/json_object_writer.h
        custom_objects/json_object_writer.cpp
        custom_objects/object_processing.h

        gui/object_widget.h
        gui/object_widget.cpp
        gui/property_widget.h
        gui/property_widget.cpp
        gui/property_widget_factory.h
        gui/property_widget_factory.cpp
        gui/property_widgets/int_property_widget.h
        gui/property_widgets/int_property_widget.cpp
        gui/property_widgets/float_property_widget.h
        gui/property_widgets/float_property_widget.cpp
        gui/property_widgets/stringlist_property_widget.h
        gui/property_widgets/stringlist_property_widget.cpp
        gui/property_widgets/icon_property_widget.h
        gui/property_widgets/icon_property_widget.cpp

        properties_config/property_info.h
        properties_config/property_info_factory.h
        properties_config/property_info_factory.cpp
        properties_config/property_processing.h
        properties_config/property_processing.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Editor
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Editor APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Editor SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Editor
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Editor PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(Editor PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS Editor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Editor)
endif()
