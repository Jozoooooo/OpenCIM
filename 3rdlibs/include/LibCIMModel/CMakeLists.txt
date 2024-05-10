cmake_minimum_required (VERSION 3.25)

project(LibCIMModel)

set(CMAKE_CXX_STANDARD 17)

# 设置库文件抽取
set(lib_output_directory ${CMAKE_SOURCE_DIR}/out/LibCIMModel) # 设置抽取目录
set(EXTRACT OFF) # 设置是否抽取

set(lib_install_directory ${CMAKE_SOURCE_DIR}/out/LibCIMModel) # 设置安装目录

if (MSVC)
    add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/utf-8>)
endif ()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/build/OpenCIM/LibCIMModel)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/build/OpenCIM/LibCIMModel)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(CMAKE_DEBUG_POSTFIX _d)
set(CMAKE_RELEASE_POSTFIX _r)

include_directories(${CMAKE_SOURCE_DIR}/3rdlibs)

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_library(LibCIMModel SHARED ${SOURCE_FILES})

add_custom_command(TARGET LibCIMModel POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:LibCIMModel> ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/../ACIMTest COMMENT "Copying libCIMModel to specified path...")
add_custom_command(TARGET LibCIMModel POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:LibCIMModel> ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/../ACIMCreator COMMENT "Copying libCIMModel to specified path...")
add_custom_command(TARGET LibCIMModel POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:LibCIMModel> ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/../ACIMViewer COMMENT "Copying libCIMModel to specified path...")
add_custom_command(TARGET LibCIMModel POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:LibCIMModel> ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/../SchemaConvert COMMENT "Copying libCIMModel to specified path...")

if(EXTRACT)
    file(GLOB_RECURSE MyLIB_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
    foreach(header_file ${MyLIB_HEADERS})
        string(FIND ${header_file} "Impl" substring_position)
        if (NOT ${substring_position} EQUAL -1)
            continue()
        endif ()

        get_filename_component(header_dir ${header_file} DIRECTORY)
        string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR} ${lib_output_directory}/include output_header_dir ${header_dir})
        file(MAKE_DIRECTORY ${output_header_dir})
        configure_file(${header_file} ${output_header_dir} COPYONLY)
    endforeach()

    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        file(COPY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/LibCIMModel_d.lib DESTINATION ${lib_output_directory}/lib)
        file(COPY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/LibCIMModel_d.dll DESTINATION ${lib_output_directory}/bin)
    else ()
        file(COPY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/LibCIMModel_r.lib DESTINATION ${lib_output_directory}/lib)
        file(COPY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/LibCIMModel_r.dll DESTINATION ${lib_output_directory}/bin)
    endif ()
endif()


install(TARGETS LibCIMModel
        LIBRARY DESTINATION ${lib_install_directory}/lib
        ARCHIVE DESTINATION ${lib_install_directory}/lib
        RUNTIME DESTINATION ${lib_install_directory}/bin
        PUBLIC_HEADER DESTINATION ${lib_install_directory}/include
)
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/" # source directory
        DESTINATION ${lib_install_directory}/include # target directory
        FILES_MATCHING # install only matched files
        PATTERN "*.hpp" # select header files
)