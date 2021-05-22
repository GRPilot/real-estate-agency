cmake_minimum_required(VERSION 3.5)

project(real-estate-agency LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

message(STATUS "Qt version: ${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}")
message(STATUS "Build directory: ${PROJECT_BINARY_DIR}")

include_directories(
    widgets/
    widgets/searchresultbuilder/
    resources/
)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    widgets/searchresultswidget.cpp
    widgets/searchwidget.cpp
    widgets/widgetmanager.cpp
    widgets/searchresultbuilder/searchresultbuilder.cpp
    resources.qrc
)
set(PROJECT_HEADERS
    mainwindow.h
    singleton.h
    widgets/searchresultswidget.h
    widgets/searchwidget.h
    widgets/widgetmanager.h
    widgets/searchresultbuilder/searchresultbuilder.h
)
set(PROJECT_UI
    mainwindow.ui
    widgets/searchwidget.ui
    widgets/searchresultswidget.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(real-estate-agency
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
        ${PROJECT_UI}
    )
else()
    add_executable(real-estate-agency
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
        ${PROJECT_UI}
    )
endif()

target_link_libraries(real-estate-agency PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
