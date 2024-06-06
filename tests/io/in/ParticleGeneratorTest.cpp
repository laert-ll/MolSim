//
// Created by Ujin on 12.05.2024.
//

#include <gtest/gtest.h>

#include "../../../src/objects/ParticleContainer.h"
#include "../../../src/io/in/ParticleGenerator.h"

//test if 2D-Cuboid is generated correctly
TEST(ParticleContainerTest, GenerateCuboid) {
    double pDistance = 1.0;
    double pMass = 1.0;
    int dimension = 2;
    CuboidParameters parameters{{0.0, 0.0, 0.0}, {2, 2, 1}, pDistance, pMass, {0.0, 0.0, 0.0}, 0.1, dimension};
    ParticleContainer container{};
    ParticleGenerator::generateCuboid(parameters, container);
    EXPECT_EQ(container.getSize(), 4);
    for (int x = 0; x < 2; x++) {
        for (int y = 0; y < 2; y++) {
            Particle particle = container.getParticles()[2 * x + y];
            EXPECT_NEAR(particle.getM(), 1.0, 1e-6);
            std::array<double, 3> expectedPosition = {static_cast<double>(x), static_cast<double>(y), 0.0};
            EXPECT_EQ(particle.getX(), expectedPosition);
        }
    }
}

//test if sample particle is created correctly
TEST(ParticleContainerTest, GenerateParticle) {
    std::array<double, 3> x = {0.0, 0.0, 0.0};
    std::array<double, 3> v = {1.0, 1.0, 1.0};
    double m = 1.5;
    double volume = 2.5;
    int t = 0;
    int dimension = 2;
    ParticleParameters parameters{x, v, m, volume, t, dimension};
    Particle particle{x, v, m, volume, t};
    Particle copy = ParticleGenerator::generateParticle(parameters);
    EXPECT_EQ(copy, particle);
}

TEST(ParticleContainerTest, GenerateDisc) {
    std::array<double, 3> center = {0.0, 0.0, 0.0};
    std::array<double, 3> startV = {0.0, 0.0, 0.0};
    int numParticlesAlongRadius = 2;
    double distanceBetweenParticles = 1.0;
    double mass = 1.0;
    int dimension = 2;
    DiscParameters parameters(center, startV, numParticlesAlongRadius, distanceBetweenParticles, mass, dimension);
    ParticleContainer container{};
    ParticleGenerator::generateDisc(parameters, container);
    EXPECT_EQ(container.getSize(), 13); // 13 particles for a disc with radius 2 in 2D
    for (auto& particle : container.getParticles()) {
        double distanceFromCenter = std::sqrt(std::pow(particle.getX()[0] - center[0], 2) + std::pow(particle.getX()[1] - center[1], 2));
        EXPECT_LE(distanceFromCenter, numParticlesAlongRadius * distanceBetweenParticles); // All particles should be within the disc's radius
        EXPECT_EQ(particle.getV(), startV);
        EXPECT_NEAR(particle.getM(), mass, 1e-6);
    }
}