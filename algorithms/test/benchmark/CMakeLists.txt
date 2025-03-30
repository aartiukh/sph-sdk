set(BENCHMARK_BIN_NAME algorithms_benchmark)

file(GLOB BENCHMARK_INC_LIST)

file(GLOB BENCHMARK_SRC_LIST "Main.cpp")

include_directories(SYSTEM ${BENCHMARK_INCLUDE_DIRECTORY})

add_executable(${BENCHMARK_BIN_NAME} ${BENCHMARK_INC_LIST} 
                                     ${BENCHMARK_SRC_LIST})

target_link_libraries(${BENCHMARK_BIN_NAME} benchmark)
