# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.25)

project (SchemaConvert)

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif ()

include_directories(${CMAKE_SOURCE_DIR}/LibCIMModel)
link_directories(${CMAKE_SOURCE_DIR}/out/build/OpenCIM/LibCIMModel)

include_directories(${CMAKE_SOURCE_DIR}/3rdlibs/xlnt/include)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Debug mode is enabled.")
    link_directories(${CMAKE_SOURCE_DIR}/3rdlibs/xlnt/lib/Debug)
else ()
    message("Release mode is enabled.")
    link_directories(${CMAKE_SOURCE_DIR}/3rdlibs/xlnt/lib/Release)
endif ()

add_executable(SchemaConvert main.cpp)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Debug mode is enabled.")
    target_link_libraries(SchemaConvert LibCIMModel_d xlntd)
else ()
    message("Release mode is enabled.")
    target_link_libraries(SchemaConvert LibCIMModel_r xlnt)
endif ()

