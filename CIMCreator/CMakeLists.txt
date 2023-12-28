cmake_minimum_required (VERSION 3.25)

project(CIMCreator)

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif ()

include_directories("${CMAKE_SOURCE_DIR}/LibCIMModel")

link_directories("${CMAKE_SOURCE_DIR}/out/build/OpenCIM/libCIMModel")

add_executable(CIMCreator
        main.cpp
        CIMStandard.cpp
        NNU-ACIM.cpp
        Mechanism/TestPlugin.cpp
        Mechanism/Plugin/HelloMechanism.cpp)

target_link_libraries(CIMCreator libCIMModel_d)
