//
// Created by kimj2 on 24.04.2024.
//

#include "../Particle.h"
#include "../Calculator.h"
#include "CalculatorTest.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <iterator>

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    std::copy(arr.cbegin(), arr.cend(), std::ostream_iterator<T>(os, " "));
    return os;
}

void CalculatorTest::initializeParticlesForTest() {
    // Initialize particles with positions, velocities, and masses
    particles.push_back(Particle({0, 0, 0}, {1, 0, 0}, 1.0));
    particles.push_back(Particle({1, 0, 0}, {0, 0, 0}, 1.0));
}

void CalculatorTest::runSimulation(double endTime, double delta_t) {
    double currentTime = 0.0;
    int iteration = 0;
    while (currentTime < endTime) {
        std::cout << "Running Test iteration " << iteration << std::endl;
        calculator.calculateX(particles, delta_t);
        calculator.calculateF(particles);
        calculator.calculateV(particles, delta_t);
        currentTime += timeStep;
    }
}

bool CalculatorTest::checkPositions() {
    std::vector<std::array<double, 3>> expectedPositions = {
            {1, 0, 0},
            {1, 0, 0}
    };

    auto it = particles.begin();
    for (size_t i = 0; i < particles.size(); ++i) {
        std::array<double, 3> expectedX = expectedPositions[i];
        std::array<double, 3> actualX = it->getX();

        std::cout << "Expected X[" << i << "]: " << expectedX << std::endl;
        std::cout << "Actual X[" << i << "]: " << actualX << std::endl;

        if (std::abs(expectedX[0] - actualX[0]) > 1e-6 ||
            std::abs(expectedX[1] - actualX[1]) > 1e-6 ||
            std::abs(expectedX[2] - actualX[2]) > 1e-6) {
            return false;
        }
        ++it;
    }
    return true;
}

void CalculatorTest::runTest() {
    std::cout << "Running calculation test with " << std::endl;
    initializeParticlesForTest();
    runSimulation(1.0, this->timeStep);
    if (checkPositions()) {
        std::cout << "PASS: Calculation ran as expected." << std::endl;
    } else {
        std::cout << "FAIL: Calculation did not run as expected." << std::endl;
    }
}

