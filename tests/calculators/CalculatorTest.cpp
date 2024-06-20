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
        void calculateFPairwise(Particle &particle1, Particle &particle2) const override{};

        void calculateLC(LinkedCellContainer &linkedCellContainer, double delta_t) override {};
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
//Testing Gravity with different Masses
TEST(CalculatorTest, GravityTest) {
    calculator->setGravity(-10.0);
    ParticleContainer container{};
//    Particle::Particle(std::array<double, 3> x_arg, std::array<double, 3> v_arg,
//            double m_arg, double volume_arg, int type_arg)
    Particle p1{{1.0, 1.0, 1.0}, {1.0, 1.0, 1.0}, 0.5, 1.0, 1};
    Particle p2{{1.0, 1.0, 1.0}, {1.0, 1.0, 1.0}, 1.0, 1.0, 1};
    Particle p3{{1.0, 1.0, 1.0}, {1.0, 1.0, 1.0}, 2.0, 1.0, 1};
    Particle p4{{1.0, 1.0, 1.0}, {1.0, 1.0, 1.0}, 5.0, 1.0, 1};

    container.addParticle(p1);
    container.addParticle(p2);
    container.addParticle(p3);
    container.addParticle(p4);

    calculator->calculateGravity(container);
    std::vector<Particle> particles = container.getParticles();

    std::vector<std::array<double, 3>> expectedForces = {{0.0, -5.0, 0.0},
                                                         {0.0, -10.0, 0.0},
                                                         {0.0, -20.0, 0.0},
                                                         {0.0, -50.0, 0.0}};
    // Iteration through vector
    for (int i = 0; i < 4; i++) {
        // Iteration through vector elements
        for (int j = 0; j < 3; j++){
            ASSERT_NEAR(particles[i].getF()[j], expectedForces[i][j], 1e-6);
        }
    }
}