cmake_minimum_required(VERSION 3.26.0)
project(ACIMViewer_Lite)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if (MSVC)
    add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/utf-8>)
endif ()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} 5.8 COMPONENTS Core Gui Widgets OpenGL REQUIRED)
message(STATUS "current Qt version is Qt${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}")

include_directories(${CMAKE_SOURCE_DIR}/3rdlibs/include)
include_directories(${CMAKE_SOURCE_DIR}/LibCIMModel)

link_directories(${CMAKE_SOURCE_DIR}/out/build/OpenCIM/LibCIMModel)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Debug mode is enabled.")
    link_directories(${CMAKE_SOURCE_DIR}/3rdlibs/lib/debug)
else ()
    message("Release mode is enabled.")
    link_directories(${CMAKE_SOURCE_DIR}/3rdlibs/lib/release)
endif ()

add_executable(ACIMViewer_Lite
        main.cpp
        Tool/OSGBTool.cpp
        Tool/OSGBTool.hpp
        ViewModel/MainWindowViewModel.cpp
        ViewModel/MainWindowViewModel.hpp
        View/ModelWidget.cpp
        View/ModelWidget.hpp
        View/MainWindow.cpp
        View/MainWindow.hpp
)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(ACIMViewer_Lite
            Qt5::Core
            Qt5::Gui
            Qt5::Widgets
            Qt5::OpenGL
            osgd
            osgQOpenGLd
            osgEarthd
            osgViewerd
            osgGAd
            osgDBd
            OpenThreadsd
            LibCIMModel_d
            proj_4_9_d
    )
else ()
    target_link_libraries(ACIMViewer_Lite
            Qt5::Core
            Qt5::Gui
            Qt5::Widgets
            Qt5::OpenGL
            osg
            osgQOpenGL
            osgEarth
            osgViewer
            osgGA
            osgDB
            OpenThreads
            LibCIMModel_r
            proj_4_9
    )
endif ()
