//
// Created by kimj2 on 11.06.2024.
//
#include "../../src/calculators/Thermostat.h"
#include "../../src/objects/ParticleContainer.h"
#include "../../src/objects/Particle.h"
#include "gtest/gtest.h"

TEST(ThermostatTest, CalculateCurrentTemp) {
    Thermostat thermostat(0.0, 0.0, 0, 1.0, 3);
    ParticleContainer particleContainer;
    std::array<double, 3> x = {0.0, 0.0, 0.0};
    std::array<double, 3> v = {1.0, 1.0, 1.0};
    Particle particle(x, v, 1.0, 0.0);
    particleContainer.addParticle(particle);

    double currentTemp = thermostat.calculateCurrentTemp(particleContainer);

    // The kinetic energy of the particle is 0.5 * m * v^2 = 0.5 * 1 * (1^2 + 1^2 + 1^2) = 1.5
    // So, the current temperature should be 2.0 / (3 * 1) * 1.5 = 1.0
    EXPECT_DOUBLE_EQ(currentTemp, 1.0);
}