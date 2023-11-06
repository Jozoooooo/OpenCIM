cmake_minimum_required(VERSION 3.25)

project(CPSViewer)

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif ()

include_directories("${CMAKE_SOURCE_DIR}/LibCIMModel")
link_directories("${CMAKE_SOURCE_DIR}/out/build/OpenCIM/LibCIMModel")

include_directories("${CMAKE_SOURCE_DIR}/3rdlibs/glfw/include")
link_directories("${CMAKE_SOURCE_DIR}/3rdlibs/glfw/lib-vc2022")

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/CIMViewer/CPSViewer/*.cpp)

add_executable(CPSViewer ${SOURCE_FILES})

# 添加需要链接的其他库
target_link_libraries(CPSViewer PRIVATE glfw3 opengl32 LibCIMModel_d)

# 忽略默认库MSVCRT
if (MSVC)
    target_link_libraries(CPSViewer PRIVATE -NODEFAULTLIB:MSVCRT)
endif ()