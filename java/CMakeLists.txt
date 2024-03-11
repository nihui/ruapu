cmake_minimum_required(VERSION 2.8)
project(ruava)
set(CMAKE_BUILD_TYPE Release)

option(BUILD_EXAMPLE OFF)

find_package(JNI REQUIRED)

add_library(ruapu_binding SHARED ruapu_binding.c)
target_include_directories(ruapu_binding PRIVATE ../ ${JNI_INCLUDE_DIRS})
install(TARGETS ruapu_binding DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/install/ruapu)

