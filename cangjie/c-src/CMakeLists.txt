cmake_minimum_required(VERSION 3.5)

project(ruapu)

include_directories(../../)


add_library(ruapu 
    ruapu-binding.c
)