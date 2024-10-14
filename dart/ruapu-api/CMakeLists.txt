cmake_minimum_required(VERSION 3.7 FATAL_ERROR)
project(ruapu_library VERSION 1.0.0 LANGUAGES C)
add_library(ruapu_library SHARED ruapu.c ruapu.def)
include_directories(../../)

set_target_properties(ruapu_library PROPERTIES
    PUBLIC_HEADER ../../ruapu.h
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    OUTPUT_NAME "ruapu"
    XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "Hex_Identity_ID_Goes_Here"
)