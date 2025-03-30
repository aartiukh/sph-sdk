if(BUILD_UNIT_TESTS)
    add_subdirectory(gtest)

    set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Disable testing for benchmark" FORCE)
    add_subdirectory(benchmark)
endif()
