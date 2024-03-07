cmake_minimum_required(VERSION 2.8)
project(ruava)
set(CMAKE_BUILD_TYPE Release)

option(BUILD_EXAMPLE OFF)

find_package(JNI REQUIRED)

add_library(ruapu_binding SHARED ruapu_binding.c)
target_include_directories(ruapu_binding PRIVATE ../ ${JNI_INCLUDE_DIRS})

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/install/ruapu/Ruapu.class
                COMMAND javac -d ${CMAKE_CURRENT_BINARY_DIR}/install ${CMAKE_CURRENT_LIST_DIR}/Ruapu.java 
                DEPENDS ${CMAKE_CURRENT_LIST_DIR}/Ruapu.java)
add_custom_target(Ruapu_class ALL SOURCES ${CMAKE_CURRENT_BINARY_DIR}/install/ruapu/Ruapu.class)

if(BUILD_EXAMPLE)
    add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/install/example.class
                    COMMAND javac   -d ${CMAKE_CURRENT_BINARY_DIR}/install 
                                    -cp ${CMAKE_CURRENT_BINARY_DIR}/install 
                                    ${CMAKE_CURRENT_LIST_DIR}/example.java
                    DEPENDS ${CMAKE_CURRENT_LIST_DIR}/example.java)
    add_custom_target(example_class ALL SOURCES ${CMAKE_CURRENT_BINARY_DIR}/install/example.class)
    add_dependencies(example_class Ruapu_class)
endif()

install(TARGETS ruapu_binding DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/install/ruapu)

