set(ALGORITHMS_TESTS_BIN_NAME algorithms_tests)

file(GLOB ALGORITHMS_TEST_SRC_LIST_INCLUDE "src/NeighboursSearchTestSuite.h"
                                           "src/ROperationsTestSuite.h"
                                           "src/MarchingCubesTestSuite.h"
                                           "src/AreaTestSuite.h"
                                           "src/VolumeTestSuite.h")

file(GLOB ALGORITHMS_TEST_SRC_LIST_SOURCE   "src/MainTest.cpp"
                                            "src/NeighboursSearchTestSuite.cpp"
                                            "src/ROperationsTestSuite.cpp"
                                            "src/MarchingCubesTestSuite.cpp"
                                            "src/AreaTestSuite.cpp"
                                            "src/VolumeTestSuite.cpp")

include_directories(SYSTEM ${GTEST_INCLUDE_DIRECTORY})

add_executable(${ALGORITHMS_TESTS_BIN_NAME} ${ALGORITHMS_SRC_LIST_INCLUDE} 
                                            ${ALGORITHMS_SRC_LIST_SOURCE}
                                            ${ALGORITHMS_TEST_SRC_LIST_INCLUDE}
                                            ${ALGORITHMS_TEST_SRC_LIST_SOURCE})

target_link_libraries(${ALGORITHMS_TESTS_BIN_NAME} gtest)

add_test(${ALGORITHMS_TESTS_BIN_NAME} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${ALGORITHMS_TESTS_BIN_NAME})
