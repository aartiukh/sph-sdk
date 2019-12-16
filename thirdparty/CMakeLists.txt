project(thirdparty)
cmake_minimum_required(VERSION 3.1)

if(BUILD_UNIT_TESTS)
    add_subdirectory(gtest)
endif()
