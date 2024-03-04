cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(ruapu_nif C CXX)

if(NOT DEFINED PRIV_DIR)
    if(DEFINED MIX_APP_PATH AND NOT "${MIX_APP_PATH}" STREQUAL "")
        if(WIN32)
            string(REPLACE "\\" "/" MIX_APP_PATH "${MIX_APP_PATH}")
        endif()
        set(PRIV_DIR "${MIX_APP_PATH}/priv")
    else()
        set(PRIV_DIR "${CMAKE_CURRENT_SOURCE_DIR}/priv")
    endif()
endif()
message(STATUS "Using PRIV_DIR: ${PRIV_DIR}")

if(DEFINED ERTS_INCLUDE_DIR AND NOT "${ERTS_INCLUDE_DIR}" STREQUAL "")
    set(ERTS_INCLUDE_DIR "${ERTS_INCLUDE_DIR}")
else()
    set(ERTS_INCLUDE_DIR_ONE_LINER "erl -noshell -eval \"io:format('~ts/erts-~ts/include/', [code:root_dir(), erlang:system_info(version)]), halt().\"")
    if(WIN32)
        execute_process(COMMAND powershell -command "${ERTS_INCLUDE_DIR_ONE_LINER}" OUTPUT_VARIABLE ERTS_INCLUDE_DIR)
    else()
        execute_process(COMMAND bash -c "${ERTS_INCLUDE_DIR_ONE_LINER}" OUTPUT_VARIABLE ERTS_INCLUDE_DIR)
    endif()
    set(ERTS_INCLUDE_DIR "${ERTS_INCLUDE_DIR}")
endif()
message(STATUS "Using ERTS_INCLUDE_DIR: ${ERTS_INCLUDE_DIR}")

if(UNIX AND APPLE)
    set(CMAKE_SHARED_LINKER_FLAGS "-flat_namespace -undefined dynamic_lookup")
endif()

if(DEFINED ENV{TARGET_GCC_FLAGS})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} $ENV{TARGET_GCC_FLAGS}")
endif()

message(STATUS "CMAKE_TOOLCHAIN_FILE: ${CMAKE_TOOLCHAIN_FILE}")

if(WIN32)
    string(REPLACE "\\" "/" C_SRC "${C_SRC}")
endif()
set(SOURCE_FILES
    "${C_SRC}/ruapu.c"
)
if(POLICY CMP0068)
    cmake_policy(SET CMP0068 NEW)
endif()

add_library(ruapu_nif SHARED
    ${SOURCE_FILES}
)
install(
    TARGETS ruapu_nif
    RUNTIME DESTINATION "${PRIV_DIR}"
)

set_target_properties(ruapu_nif PROPERTIES PREFIX "")
if(NOT WIN32)
    set_target_properties(ruapu_nif PROPERTIES SUFFIX ".so")
endif()
set_target_properties(ruapu_nif PROPERTIES
    INSTALL_RPATH_USE_LINK_PATH TRUE
    BUILD_WITH_INSTALL_RPATH TRUE
)
if(EXISTS "${C_SRC}/ruapu.h")
    target_include_directories(ruapu_nif PUBLIC "${ERTS_INCLUDE_DIR}")
else()
    target_include_directories(ruapu_nif PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/.." "${ERTS_INCLUDE_DIR}")
endif()

if(UNIX AND NOT APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-but-set-variable -Wno-reorder")
elseif(UNIX AND APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-reorder-ctor")
    set(CMAKE_SHARED_LINKER_FLAGS "-flat_namespace -undefined dynamic_lookup")
endif()

if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj /wd4996 /wd4267 /wd4068")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
    endif()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-function -Wno-sign-compare -Wno-unused-parameter -Wno-missing-field-initializers -Wno-deprecated-declarations")
endif()
