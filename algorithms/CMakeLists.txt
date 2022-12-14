set(ALGORITHMS_LIB_NAME algorithms)

file(GLOB ALGORITHMS_SRC_LIST_INCLUDE "src/NeighboursSearch.h"
                                      "src/NeighboursSearch.hpp"
                                      "src/Point.h"
                                      "src/Point.hpp"
                                      "src/Defines.h"
                                      "src/Area.h"
                                      "src/ROperations.h"
                                      "src/ROperations.hpp"
                                      "src/MarchingCubes.h"
                                      "src/MarchingCubesConfig.h"
                                      "src/Shapes.h")

file(GLOB ALGORITHMS_SRC_LIST_SOURCE "src/Area.cpp"
                                     "src/MarchingCubes.cpp")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

if(BUILD_UNIT_TESTS)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
endif()

add_library(${ALGORITHMS_LIB_NAME} ${ALGORITHMS_SRC_LIST_INCLUDE} ${ALGORITHMS_SRC_LIST_SOURCE})
