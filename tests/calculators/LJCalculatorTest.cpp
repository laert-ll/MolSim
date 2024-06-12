#include "../../src/calculators/Calculator.h"
#include "../../src/calculators/LJCalculator.h"
#include "../../src/objects/Particle.h"
#include "../../src/objects/ParticleContainer.h"
#include "gtest/gtest.h"

namespace {
    const double sigma = 1.0;
    const double epsilon = 5.0;
    const auto calculator = std::make_unique<calculators::LJCalculator>(5.31608);
}

TEST(LJCalculatorTest, CalculateFTest) {
    ParticleContainer pc;
    pc.addParticle(Particle({0.25, 0.25, 0.25}, {0, 0, 0}, 1.0, 0.0));
    pc.addParticle(Particle({-0.25, -0.25, -0.25}, {0, 0, 0}, 1.0, 0.0));
    pc.initializePairs();
    pc.setVolumes();

    const int iteration = 1;

    for (int i = 0; i < iteration; ++i) {
        calculator->calculateF(pc);
    }

    const std::vector<std::array<double, 3>> expectedForces = {
            {709.355, 709.355, 709.355},
            {-709.355, -709.355, -709.355}
    };

    auto it = pc.begin();
    for (size_t i = 0; i < pc.getSize(); ++i, ++it) {
        std::array<double, 3> expectedF = expectedForces[i];
        std::array<double, 3> actualF = it->getF();
        EXPECT_NEAR(expectedF[0], actualF[0], 1e-3);
        EXPECT_NEAR(expectedF[1], actualF[1], 1e-3);
        EXPECT_NEAR(expectedF[2], actualF[2], 1e-3);
    }
}