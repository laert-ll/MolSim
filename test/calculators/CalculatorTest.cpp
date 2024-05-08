#include "../../src/calculators/Calculator.h"
#include "../../src/calculators/SVCalculator.h"
#include "../../src/objects/Particle.h"
#include "../../src/objects/ParticleContainer.h"
#include "gtest/gtest.h"

TEST(CalculatorTest, Positions) {
    ParticleContainer pc;
    pc.addParticle(Particle({1, 1, 1}, {0, 0, 0}, 1.0, 0.0));
    pc.addParticle(Particle({-1, -1, -1}, {0, 0, 0}, 1.0, 0.0));
    pc.initializePairs();
    pc.setVolumes();

    auto calculator = std::make_unique<calculators::SVCalculator>();
    double endTime = 5.0;
    double delta_t = 0.1;
    double currentTime = 0.0;

    while (currentTime < endTime) {
        calculator->calculate(pc, delta_t);
        currentTime += delta_t;
    }

    std::vector<std::array<double, 3>> expectedPositions = {
        {0.0478651,  0.0478651,  0.0478651},
        {-0.0478651, -0.0478651, -0.0478651}
    };

    auto it = pc.begin();
    for (size_t i = 0; i < pc.getSize(); ++i, ++it) {
        std::array<double, 3> expectedX = expectedPositions[i];
        std::array<double, 3> actualX = it->getX();
        EXPECT_NEAR(expectedX[0], actualX[0], 1e-6);
        EXPECT_NEAR(expectedX[1], actualX[1], 1e-6);
        EXPECT_NEAR(expectedX[2], actualX[2], 1e-6);
    }
}
