//
// Created by kimj2 on 14.05.2024.
//

#include "../../src/calculators/Calculator.h"
#include "../../src/calculators/LJCalculator.h"
#include "../../src/objects/Particle.h"
#include "../../src/objects/ParticleContainer.h"
#include "gtest/gtest.h"

namespace calculators {
    class TestCalculator : public calculators::Calculator {
    private:
//        void calculateF(ParticleContainer &particleContainer) override {};
        void calculateFpair(Particle &particle1, Particle &particle2) override{};
    };
}

namespace {
    const auto calculator = std::make_unique<calculators::TestCalculator>();
}

TEST(CalculatorTest, CalculateXTest) {
    Particle particle1({1, 1, 1}, {-1, -1, -1}, 1.0, 0.0);
    particle1.setF({-1, -1, -1});
    Particle particle2({-1, -1, -1}, {1, 1, 1}, 1.0, 0.0);
    particle2.setF({1, 1, 1});

    ParticleContainer pc;
    pc.addParticle(std::ref(particle1));
    pc.addParticle(std::ref(particle2));
    pc.initializePairs();
    pc.setVolumes();

    const double delta_t = 0.1;
    const int iteration = 1;

    for (int i = 0; i < iteration; ++i) {
        calculator->calculateX(pc, delta_t);
    }

    const std::vector<std::array<double, 3>> expectedPositions = {
            {0.8950,  0.8950,  0.8950},
            {-0.8950, -0.8950, -0.8950}
    };

    auto it = pc.begin();
    for (size_t i = 0; i < pc.getSize(); ++i, ++it) {
        std::array<double, 3> expectedX = expectedPositions[i];
        std::array<double, 3> actualX = it->getX();
        EXPECT_NEAR(expectedX[0], actualX[0], 1e-3);
        EXPECT_NEAR(expectedX[1], actualX[1], 1e-3);
        EXPECT_NEAR(expectedX[2], actualX[2], 1e-3);
    }
}

TEST(CalculatorTest, CalculateVTest) {
    Particle particle1({1, 1, 1}, {0, 0, 0}, 1.0, 0.0);
    particle1.setF({-1, -1, -1});
    Particle particle2({-1, -1, -1}, {0, 0, 0}, 1.0, 0.0);
    particle2.setF({1, 1, 1});

    ParticleContainer pc;
    pc.addParticle(std::ref(particle1));
    pc.addParticle(std::ref(particle2));
    pc.initializePairs();
    pc.setVolumes();

    const double delta_t = 0.1;
    const int iteration = 1;

    for (int i = 0; i < iteration; ++i) {
        calculator->calculateV(pc, delta_t);
    }

    const std::vector<std::array<double, 3>> expectedVelocities = {
            {-0.0500, -0.0500, -0.0500},
            {0.0500, 0.0500, 0.0500}
    };

    auto it = pc.begin();
    for (size_t i = 0; i < pc.getSize(); ++i, ++it) {
        std::array<double, 3> expectedV = expectedVelocities[i];
        std::array<double, 3> actualV = it->getV();
        EXPECT_NEAR(expectedV[0], actualV[0], 1e-3);
        EXPECT_NEAR(expectedV[1], actualV[1], 1e-3);
        EXPECT_NEAR(expectedV[2], actualV[2], 1e-3);
    }
}