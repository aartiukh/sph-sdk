set(SPH_TESTS_BIN_NAME sph_tests)

file(GLOB SPH_TEST_SRC_LIST_INCLUDE "src/ParticleTestSuite.h"
                                    "src/ForcesTestSuite.h"
                                    "src/CollisionsTestSuite.h"
                                    "src/IntegratorTestSuite.h")
file(GLOB SPH_TEST_SRC_LIST_SOURCE  "src/MainTest.cpp"
                                    "src/ParticleTestSuite.cpp"
                                    "src/ForcesTestSuite.cpp"
                                    "src/CollisionsTestSuite.cpp"
                                    "src/IntegratorTestSuite.cpp")

include_directories(SYSTEM ${GTEST_INCLUDE_DIRECTORY})

add_executable(${SPH_TESTS_BIN_NAME} ${SPH_SRC_LIST_INCLUDE}
                                     ${SPH_SRC_LIST_SOURCE}
                                     ${SPH_TEST_SRC_LIST_INCLUDE}
                                     ${SPH_TEST_SRC_LIST_SOURCE})

target_link_libraries(${SPH_TESTS_BIN_NAME} gtest algorithms sph)

add_test(${SPH_TESTS_BIN_NAME} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${SPH_TESTS_BIN_NAME})
