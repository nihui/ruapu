cmake_minimum_required(VERSION 3.0)

project(ruapu-fortran)

enable_language(Fortran)

include_directories(../)

add_library(ruapu
    src/ruapu-binding.c
    src/ruapu-binding.f90
)

add_executable(${PROJECT_NAME}
    src/main.f90
)

target_link_libraries(${PROJECT_NAME} ruapu)

set_target_properties(
    ruapu-fortran
    PROPERTIES
    LINKER_LANGUAGE Fortran
)
