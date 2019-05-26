project(algorithms)
cmake_minimum_required(VERSION 3.1)

file(GLOB ALGORITHMS_SRC_LIST_INCLUDE "${PROJECT_SOURCE_DIR}/src/NeighboursSearch.h"
                                      "${PROJECT_SOURCE_DIR}/src/NeighboursSearch.hpp"
                                      "${PROJECT_SOURCE_DIR}/src/Point.h"
                                      "${PROJECT_SOURCE_DIR}/src/Point.hpp"
                                      "${PROJECT_SOURCE_DIR}/src/Defines.h"
                                      "${PROJECT_SOURCE_DIR}/src/Area.h"
                                      "${PROJECT_SOURCE_DIR}/src/ROperations.h")

file(GLOB ALGORITHMS_SRC_LIST_SOURCE  "${PROJECT_SOURCE_DIR}/src/Area.cpp"
                                      "${PROJECT_SOURCE_DIR}/src/ROperations.cpp")

include_directories(${PROJECT_SOURCE_DIR}/src)

if(BUILD_UNIT_TESTS)
    add_subdirectory(${PROJECT_SOURCE_DIR}/test)
endif()

add_library(${PROJECT_NAME} ${ALGORITHMS_SRC_LIST_INCLUDE} ${ALGORITHMS_SRC_LIST_SOURCE})

file(GLOB MARCHING_CUBES_SRC_LIST_INCLUDE "${PROJECT_SOURCE_DIR}/src/marching-cubes/MarchingCubes.h"
                                          "${PROJECT_SOURCE_DIR}/src/marching-cubes/MarchingCubesConfig.h")

file(GLOB MARCHING_CUBES_SRC_LIST_SOURCE  "${PROJECT_SOURCE_DIR}/src/marching-cubes/MarchingCubes.cpp"
                                          "${PROJECT_SOURCE_DIR}/src/marching-cubes/Main.cpp")

add_executable(marching-cubes ${MARCHING_CUBES_SRC_LIST_INCLUDE} ${MARCHING_CUBES_SRC_LIST_SOURCE})
target_link_libraries(marching-cubes ${PROJECT_NAME})
                                    
