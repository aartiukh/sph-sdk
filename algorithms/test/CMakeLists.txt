project(algorithms_tests)
cmake_minimum_required(VERSION 2.8)

file(GLOB ALGORITHMS_TEST_SRC_LIST_INCLUDE "${PROJECT_SOURCE_DIR}/src/NeighboursSearchTestSuite.h"
                                           "${PROJECT_SOURCE_DIR}/src/ROperationsTestSuite.h"
                                           "${PROJECT_SOURCE_DIR}/src/MarchingCubesTestSuite.h")

file(GLOB ALGORITHMS_TEST_SRC_LIST_SOURCE   "${PROJECT_SOURCE_DIR}/src/MainTest.cpp"
                                            "${PROJECT_SOURCE_DIR}/src/NeighboursSearchTestSuite.cpp"
                                            "${PROJECT_SOURCE_DIR}/src/ROperationsTestSuite.cpp"
                                            "${PROJECT_SOURCE_DIR}/src/MarchingCubesTestSuite.cpp")

include_directories(SYSTEM ${GTEST_INCLUDE_DIRECTORY})

add_executable(${PROJECT_NAME} ${ALGORITHMS_SRC_LIST_INCLUDE} 
                               ${ALGORITHMS_SRC_LIST_SOURCE}
                               ${ALGORITHMS_TEST_SRC_LIST_INCLUDE}
                               ${ALGORITHMS_TEST_SRC_LIST_SOURCE})

target_link_libraries(${PROJECT_NAME} gtest)

add_test(${PROJECT_NAME} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME})
