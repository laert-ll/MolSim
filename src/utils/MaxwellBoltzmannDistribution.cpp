//
// Created by kimj2 on 12.06.2024.
//
#include "MaxwellBoltzmannDistribution.h"
#include <random>
#include <array>
#include <spdlog/spdlog.h>

std::array<double, 3> maxwellBoltzmannDistributedVelocity(double averageVelocity, size_t dimensions) {
    static std::default_random_engine randomEngine(42);
    std::normal_distribution<double> normalDistribution{0, 1};
    std::array<double, 3> randomVelocity{};
    for (size_t i = 0; i < dimensions; ++i) {
        randomVelocity[i] = averageVelocity * normalDistribution(randomEngine);
    }
    SPDLOG_TRACE("Generated random velocity: [{}, {}, {}]", randomVelocity[0], randomVelocity[1], randomVelocity[2]);
    return randomVelocity;
}