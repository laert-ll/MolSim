//
// Created by kimj2 on 24.04.2024.
//

#include "../Particle.h"
#include "../Calculator.h"
#include <iostream>
#include <vector>
#include <cmath>

class CalculatorTest {
private:
    std::list<Particle> particles;
    double timeStep;
    Calculator calculator;

public:
    CalculatorTest(double delta_t) : timeStep(delta_t), calculator(Calculator()) {}

    void initializeParticlesForTest() {
        // Initialize particles with positions, velocities, and masses
        particles.push_back(Particle({0, 0, 0}, {1, 0, 0}, 1.0)); // Particle 1
        particles.push_back(Particle({1, 0, 0}, {0, 0, 0}, 1.0)); // Particle 2
    }

    void runSimulation(double endTime, double delta_t) {
        double currentTime = 0.0;
        while (currentTime < endTime) {
            calculator.calculateX(particles, delta_t);
            calculator.calculateF(particles);
            calculator.calculateV(particles, delta_t);
            currentTime += timeStep;
        }
    }

    bool checkPositions() {
        std::vector<std::array<double, 3>> expectedPositions = {
                {0.5, 0, 0},
                {1.5, 0, 0}
        };

        auto it = particles.begin();
        for (size_t i = 0; i < particles.size(); ++i) {
            std::array<double, 3> expectedX = expectedPositions[i];
            std::array<double, 3> actualX = it->getX();
            if (std::abs(expectedX[0] - actualX[0]) > 1e-6 ||
                std::abs(expectedX[1] - actualX[1]) > 1e-6 ||
                std::abs(expectedX[2] - actualX[2]) > 1e-6) {
                return false;
            }
            ++it;
        }
        return true;
    }

    void runTest() {
        initializeParticlesForTest();
        runSimulation(1.0, this->timeStep); // Run the simulation for 1 time unit
        if (checkPositions()) {
            std::cout << "PASS: Calculation ran as expected." << std::endl;
        } else {
            std::cout << "FAIL: Calculation did not run as expected." << std::endl;
        }
    }
};

int main() {
    CalculatorTest testRunner(0.1);
    testRunner.runTest();
    return 0;
}

