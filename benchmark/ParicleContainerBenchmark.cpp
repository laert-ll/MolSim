#include "../src/objects/ParticleContainer.h"
#include "../src/objects/Particle.h"
#include "benchmark/benchmark.h"

class ParticleContainerBenchmark : public benchmark::Fixture {
protected:
    ParticleContainer pc;

    void SetUp(const ::benchmark::State& state) {
        for (int i = 0; i < state.range(0); ++i) {
            Particle p(i);
            pc.addParticle(p);
        }
    }
};

// Benchmark for adding particles to ParticleContainer
BENCHMARK_DEFINE_F(ParticleContainerBenchmark, BM_AddParticles)(benchmark::State& state) {
    for (auto _ : state) {
        // Print out the number of iterations
        printf("Iterations: %d\n", state.iterations());
        
        // Add particles to ParticleContainer
        for (int i = 0; i < state.range(0); ++i) {
            Particle p(i);
            pc.addParticle(p);
        }
    }
}

// Register the benchmark for adding particles
BENCHMARK_REGISTER_F(ParticleContainerBenchmark, BM_AddParticles)
    ->RangeMultiplier(2)
    ->Range(2, 100);

// Benchmark for initializing pairs in ParticleContainer
BENCHMARK_DEFINE_F(ParticleContainerBenchmark, BM_InitializePairs)(benchmark::State& state) {
    for (auto _ : state) {
        pc.initializePairs();
    }
}

// Register the benchmark for initializing pairs
BENCHMARK_REGISTER_F(ParticleContainerBenchmark, BM_InitializePairs)
    ->RangeMultiplier(2)
    ->Range(2, 100);

// Entry point to run the benchmarks
BENCHMARK_MAIN();
