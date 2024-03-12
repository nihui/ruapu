cmake_minimum_required(VERSION 3.0)

project(ruapu)

include_directories(../)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)

add_library(ruapu 
    ruapu-binding.c
)

