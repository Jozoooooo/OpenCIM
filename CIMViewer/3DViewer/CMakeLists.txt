cmake_minimum_required(VERSION 3.25)

project(3DViewer)

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif ()

include_directories("${CMAKE_SOURCE_DIR}/LibCIMModel")
link_directories("${CMAKE_SOURCE_DIR}/out/build/OpenCIM/LibCIMModel")

include_directories("${CMAKE_SOURCE_DIR}/3rdlibs/vtk/include")
link_directories("${CMAKE_SOURCE_DIR}/3rdlibs/vtk/lib/debug")

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/CIMViewer/3DViewer/*.cpp)
file(GLOB_RECURSE VTK_LIBS ${CMAKE_SOURCE_DIR}/3rdlibs/vtk/lib/debug/*.lib)

add_executable(3DViewer ${SOURCE_FILES})

# 添加需要链接的其他库
target_link_libraries(3DViewer PRIVATE LibCIMModel_d ${VTK_LIBS})