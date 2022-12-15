cmake_policy(SET CMP0048 NEW)
project(sph-sdk VERSION 1.0.0 LANGUAGES CXX)
cmake_minimum_required(VERSION 3.1)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/Modules")

if(MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
    set(CMAKE_CXX_FLAGS_RELEASE "/MT")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX /wd4548 /wd4251 /wd4514 /wd4668 /wd4820 /wd4710 /wd4625 /wd4626 /wd4826 /wd4505")
endif()

include_directories(.)

# Third party folder
set(THIRDPARTY_DIR ${PROJECT_SOURCE_DIR}/thirdparty)

set(GTEST_INCLUDE_DIRECTORY "${PROJECT_SOURCE_DIR}/thirdparty/gtest/include")

if(NOT DEFINED BUILD_UNIT_TESTS)
    set(BUILD_UNIT_TESTS 1)
endif()

if (BUILD_UNIT_TESTS)
    include(CTest)
    enable_testing()
endif()

add_subdirectory(thirdparty)
add_subdirectory(algorithms)
add_subdirectory(sph)
# add_subdirectory(demo)
