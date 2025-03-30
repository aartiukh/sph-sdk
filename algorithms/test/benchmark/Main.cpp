#include "NSBruteForce.h"
#include "NSBruteForceImproved.h"
#include "Point.h"

#include <benchmark/benchmark.h>

struct TestParticle
{
    SPHSDK::Point3<SPHSDK::FLOAT> position;
    std::vector<size_t>           neighbours;
};

static const size_t              PARTICLE_COUNT = 1000;
static std::vector<TestParticle> particles(PARTICLE_COUNT);

static const SPHSDK::Volume volume;
static const SPHSDK::FLOAT  radius = 1.0f;
static const SPHSDK::FLOAT  eps = 0.1f;

static void DoSetup(const benchmark::State& state)
{
    // Create a vector of TestParticle objects
    std::vector<TestParticle> particles(PARTICLE_COUNT);
    for (size_t i = 0; i < particles.size(); ++i)
    {
        particles[i].position = SPHSDK::Point3<SPHSDK::FLOAT>(
            static_cast<SPHSDK::FLOAT>(i), static_cast<SPHSDK::FLOAT>(i), static_cast<SPHSDK::FLOAT>(i));
    }
}

static void BM_BruteForce(benchmark::State& state)
{
    SPHSDK::NSBruteForce<std::vector<TestParticle>> bruteForce(volume, radius, eps);

    for (auto _ : state)
    {
        bruteForce.search(particles);
    }
}

BENCHMARK(BM_BruteForce);

static void BM_BruteForceImproved(benchmark::State& state)
{
    SPHSDK::NSBruteForceImproved<std::vector<TestParticle>> bruteForceImproved(volume, radius, eps);

    for (auto _ : state)
    {
        bruteForceImproved.search(particles);
    }
}

BENCHMARK(BM_BruteForceImproved);

// Run the benchmark
BENCHMARK_MAIN();
