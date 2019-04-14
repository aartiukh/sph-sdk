project(thirdparty)
cmake_minimum_required(VERSION 2.8)

if(BUILD_UNIT_TESTS)
    add_subdirectory(gtest)
endif()
