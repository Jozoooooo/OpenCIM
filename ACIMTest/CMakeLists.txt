cmake_minimum_required (VERSION 3.25)

project(Code)

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif ()

include_directories(${CMAKE_SOURCE_DIR}/LibCIMModel)

link_directories(${CMAKE_SOURCE_DIR}/out/build/OpenCIM/libCIMModel)

add_executable(ACIMTest
        main.cpp
        CIMSchema.cpp
        CIMSynthetic.cpp
        Mechanism/TestPlugin.cpp
        Mechanism/Plugin/HelloMechanism.cpp
        CIMDataSet.cpp)

target_link_libraries(ACIMTest libCIMModel_d)
