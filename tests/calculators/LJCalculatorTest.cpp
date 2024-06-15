#include "../../src/calculators/Calculator.h"
#include "../../src/calculators/LJCalculator.h"
#include "../../src/objects/Particle.h"
#include "../../src/objects/ParticleContainer.h"
#include "gtest/gtest.h"

namespace {
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

TEST(LJCalculatorTest, DifferentSigma) {
    ParticleContainer pc;
    //    Particle(std::array<double, 3> x_arg, std::array<double, 3> v_arg,
    //             double m_arg, double volume_arg, int type_arg, double sig_arg, double eps_arg);
    Particle p1{{1.0, 0.0, 0.0}, {0, 0, 0}, 1.0, 0.0, 1, 2.5, 5};
    Particle p2{{2.0, 0.0, 0.0}, {0, 0, 0}, 1.0, 0.0, 1, 3.5, 5};

    calculator->calculateFPairwise(p1, p2);

    const std::vector<std::array<double, 3>> expectedForces = {
            {-20000.0, 0.0, 0.0},
            {20000.0, 0.0, 0.0}
    };
    pc.addParticle(p1);
    pc.addParticle(p2);

    auto it = pc.begin();
    for (size_t i = 0; i < pc.getSize(); ++i, ++it) {
        std::array<double, 3> expectedF = expectedForces[i];
        std::array<double, 3> actualF = it->getF();
        EXPECT_NEAR(expectedF[0], actualF[0], 1e-3);
        EXPECT_NEAR(expectedF[1], actualF[1], 1e-3);
        EXPECT_NEAR(expectedF[2], actualF[2], 1e-3);
    }
}

TEST(LJCalculatorTest, DifferentEpsilon) {
    ParticleContainer pc;
    //    Particle(std::array<double, 3> x_arg, std::array<double, 3> v_arg,
    //             double m_arg, double volume_arg, int type_arg, double sig_arg, double eps_arg);
    Particle p1{{1.0, 0.0, 0.0}, {0, 0, 0}, 1.0, 0.0, 1, 3.0, 2};
    Particle p2{{2.0, 0.0, 0.0}, {0, 0, 0}, 1.0, 0.0, 1, 3.0, 12.5};

    calculator->calculateFPairwise(p1, p2);

    const std::vector<std::array<double, 3>> expectedForces = {
            {-20000.0, 0.0, 0.0},
            {20000.0, 0.0, 0.0}
    };
    pc.addParticle(p1);
    pc.addParticle(p2);

    auto it = pc.begin();
    for (size_t i = 0; i < pc.getSize(); ++i, ++it) {
        std::array<double, 3> expectedF = expectedForces[i];
        std::array<double, 3> actualF = it->getF();
        EXPECT_NEAR(expectedF[0], actualF[0], 1e-3);
        EXPECT_NEAR(expectedF[1], actualF[1], 1e-3);
        EXPECT_NEAR(expectedF[2], actualF[2], 1e-3);
    }
}

