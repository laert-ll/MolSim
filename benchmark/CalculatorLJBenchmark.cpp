#include "../src/calculators/Calculator.h"
#include "../src/calculators/LJCalculator.h"
#include "../src/objects/ParticleContainer.h"
#include "../src/io/in/TXTReader.h"
#include "benchmark/benchmark.h"
#include <memory>

static void BM_LJCalculator(benchmark::State& state) {
    const double delta_t = state.range(0) == 0 ? 0.01 :
                            state.range(0) == 1 ? 0.005 :
                            state.range(0) == 2 ? 0.001 :
                            state.range(0) == 3 ? 0.0005 : 5;
    const double end_time = 5.0;
    std::unique_ptr<calculators::Calculator> calculator = std::make_unique<calculators::LJCalculator>(1, 5, 5.31608);
    ParticleContainer particleContainer = fileReaders::TXTReader::readFile("../resources/input-cuboid.txt");

    for (auto _ : state) {
        double current_time = 0;
        while (current_time < end_time) {
            calculator->calculate(particleContainer, delta_t);
            current_time += delta_t;
        }
    }

    state.SetLabel(std::to_string(delta_t));
}

BENCHMARK(BM_LJCalculator)->Unit(benchmark::kMillisecond)->Arg(0)->Arg(1)->Arg(2)->Arg(3)->Iterations(5);

BENCHMARK_MAIN();
