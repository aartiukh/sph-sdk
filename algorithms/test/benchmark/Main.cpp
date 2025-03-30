#include <benchmark/benchmark.h>

void SomeFunction() {
  // Simulate some work
  for (int i = 0; i < 1000; ++i) {
    // Do some computation
  }
}

static void BM_SomeFunction(benchmark::State& state) {
  // Perform setup here
  for (auto _ : state) {
    // This code gets timed
    SomeFunction();
  }
}
// Register the function as a benchmark
BENCHMARK(BM_SomeFunction);
// Run the benchmark
BENCHMARK_MAIN();
