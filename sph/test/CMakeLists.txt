project(sph_tests)
cmake_minimum_required(VERSION 2.8)

file(GLOB SPH_TEST_SRC_LIST_INCLUDE "${PROJECT_SOURCE_DIR}/src/ParticleTestSuite.h"
                                    "${PROJECT_SOURCE_DIR}/src/ForcesTestSuite.h"
                                    "${PROJECT_SOURCE_DIR}/src/CollisionsTestSuite.h"
                                    "${PROJECT_SOURCE_DIR}/src/IntegratorTestSuite.h")
file(GLOB SPH_TEST_SRC_LIST_SOURCE  "${PROJECT_SOURCE_DIR}/src/MainTest.cpp"
                                    "${PROJECT_SOURCE_DIR}/src/ParticleTestSuite.cpp"
                                    "${PROJECT_SOURCE_DIR}/src/ForcesTestSuite.cpp"
                                    "${PROJECT_SOURCE_DIR}/src/CollisionsTestSuite.cpp"
                                    "${PROJECT_SOURCE_DIR}/src/IntegratorTestSuite.cpp")

include_directories(SYSTEM ${GTEST_INCLUDE_DIRECTORY})

add_executable(${PROJECT_NAME} ${SPH_SRC_LIST_INCLUDE}
                               ${SPH_SRC_LIST_SOURCE}
                               ${SPH_TEST_SRC_LIST_INCLUDE}
                               ${SPH_TEST_SRC_LIST_SOURCE})

target_link_libraries(${PROJECT_NAME} gtest algorithms sph)

add_test(${PROJECT_NAME} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME})
