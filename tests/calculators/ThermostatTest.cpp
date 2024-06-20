//
// Created by kimj2 on 11.06.2024.
//
#include "../../src/calculators/Thermostat.h"
#include "../../src/objects/LinkedCellContainer.h"
#include "../../src/objects/Particle.h"
#include "gtest/gtest.h"

TEST(ThermostatTest, CalculateCurrentTempTest) {
    Thermostat thermostat(0.0, 0.0, 0, 1.0, 3);
    LinkedCellContainer linkedCellContainer;
    std::array<double, 3> x = {0.0, 0.0, 0.0};
    std::array<double, 3> v = {1.0, 1.0, 1.0};
    auto particle = std::make_shared<Particle>(x, v, 1.0, 0.0);
    linkedCellContainer.addParticle(particle);

    double currentTemp = thermostat.calculateCurrentTemp(linkedCellContainer);

    // The kinetic energy of the particle is 0.5 * m * v^2 = 0.5 * 1 * (1^2 + 1^2 + 1^2) = 1.5
    // So, the current temperature should be 2.0 / (3 * 1) * 1.5 = 1.0
    EXPECT_DOUBLE_EQ(currentTemp, 1.0);
}

TEST(ThermostatTest, InitializeTempTest) {
    const Thermostat thermostat(10.0, 20.0, 1, 1.0, 3);
    LinkedCellContainer linkedCellContainer;
    const std::array<double, 3> x = {0.0, 0.0, 0.0};
    const std::array<double, 3> v = {0.0, 0.0, 0.0}; // Initial velocities are zero
    auto particle1 = std::make_shared<Particle>(x, v, 1.0, 0.0);
    auto particle2 = std::make_shared<Particle>(x, v, 1.0, 0.0);
    linkedCellContainer.addParticle(particle1);
    linkedCellContainer.addParticle(particle2);

    thermostat.initializeTemp(linkedCellContainer);

    for (auto &particle: linkedCellContainer) {
        const auto &velocities = particle->getV();
        for (int i = 0; i < 3; ++i) {
            EXPECT_NE(velocities[i], 0.0);
        }
    }

    const double currentTemp = thermostat.calculateCurrentTemp(linkedCellContainer);
    EXPECT_NEAR(currentTemp, 10.0, 1e-3);
}

TEST(ThermostatTest, SetTempDirectlyTest) {
    const double initialTemp = 10.0;
    const double targetTemp = 20.0;
    const Thermostat thermostat(initialTemp, targetTemp, 1, 1.0, 3);
    LinkedCellContainer linkedCellContainer;
    const std::array<double, 3> x = {0.0, 0.0, 0.0};
    const std::array<double, 3> v = {1.0, 1.0, 1.0};
    auto particle = std::make_shared<Particle>(x, v, 1.0, 0.0);
    linkedCellContainer.addParticle(particle);

    thermostat.initializeTemp(linkedCellContainer);

    thermostat.setTempDirectly(linkedCellContainer);

    const double currentTemp = thermostat.calculateCurrentTemp(linkedCellContainer);
    EXPECT_NEAR(currentTemp, targetTemp, 1e-3);
}

TEST(ThermostatTest, SetTempGraduallyTest) {
    const double initialTemp = 10.0;
    const double targetTemp = 20.0;
    const double maxDeltaTemp = 1.0;
    const Thermostat thermostat(initialTemp, targetTemp, 1, maxDeltaTemp, 3);
    LinkedCellContainer linkedCellContainer;
    const std::array<double, 3> x = {0.0, 0.0, 0.0};
    const std::array<double, 3> v = {1.0, 1.0, 1.0}; // Initial velocities set to achieve the initial temperature
    auto particle = std::make_shared<Particle>(x, v, 1.0, 0.0);
    linkedCellContainer.addParticle(particle);

    thermostat.initializeTemp(linkedCellContainer);

    thermostat.setTempGradually(linkedCellContainer);

    const double currentTemp = thermostat.calculateCurrentTemp(linkedCellContainer);
    const double expectedTemp = initialTemp + maxDeltaTemp;
    EXPECT_NEAR(currentTemp, expectedTemp, 1e-3);
}
