project(algorithms)
cmake_minimum_required(VERSION 2.8)

file(GLOB ALGORITHMS_SRC_LIST_INCLUDE "${PROJECT_SOURCE_DIR}/include/NeighboursSearch.h"
                                      "${PROJECT_SOURCE_DIR}/include/NeighboursSearch.hpp"
                                      "${PROJECT_SOURCE_DIR}/include/Point.h"
                                      "${PROJECT_SOURCE_DIR}/include/Point.hpp"
                                      "${PROJECT_SOURCE_DIR}/include/Defines.h"
                                      "${PROJECT_SOURCE_DIR}/include/Area.h")

file(GLOB ALGORITHMS_SRC_LIST_SOURCE  "${PROJECT_SOURCE_DIR}/src/Area.cpp")

include_directories(${PROJECT_SOURCE_DIR}/include)

if(BUILD_UNIT_TESTS)
    add_subdirectory(${PROJECT_SOURCE_DIR}/test)
endif()

add_library(${PROJECT_NAME} ${ALGORITHMS_SRC_LIST_INCLUDE} ${ALGORITHMS_SRC_LIST_SOURCE})
