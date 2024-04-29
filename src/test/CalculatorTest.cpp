// //
// // Created by kimj2 on 24.04.2024.
// //

// #include "../Particle.h"
// #include "../Calculator.h"
// #include "CalculatorTest.h"
// #include <iostream>
// #include <vector>
// #include <cmath>
// #include <iterator>

// template<typename T, std::size_t N>
// std::ostream &operator<<(std::ostream &os, const std::array<T, N> &arr) {
//     std::copy(arr.cbegin(), arr.cend(), std::ostream_iterator<T>(os, " "));
//     return os;
// }

// void CalculatorTest::initializeParticlesForTest() {
//     particles.push_back(Particle({1, 1, 1}, {0, 0, 0}, 1.0));
//     particles.push_back(Particle({-1, -1, -1}, {0, 0, 0}, 1.0));
// }

// void CalculatorTest::runSimulation(double endTime, double delta_t) {
//     double currentTime = 0.0;
//     int iteration = 0;
//     while (currentTime < endTime) {
//         std::cout << "Running Test iteration " << iteration << std::endl;
//         calculator.calculateX(particles, delta_t);
//         calculator.calculateF(particles);
//         calculator.calculateV(particles, delta_t);

//         int i = 0;
//         for (auto it = particles.begin(); it != particles.end(); ++it, ++i) {
//             std::cout << "Particle " << i << ": " << std::endl;
//             std::cout << *it << std::endl;
//         }

//         currentTime += delta_t;
//         iteration++;
//     }
// }

// bool CalculatorTest::checkPositions() {
//     bool result = true;
//     std::vector<std::array<double, 3>> expectedPositions = {
//             {0.0478651,  0.0478651,  0.0478651},
//             {-0.0478651, -0.0478651, -0.0478651}
//     };

//     auto it = particles.begin();
//     for (size_t i = 0; i < particles.size(); ++i) {
//         std::array<double, 3> expectedX = expectedPositions[i];
//         std::array<double, 3> actualX = it->getX();

//         std::cout << "Expected X[" << i << "]: " << expectedX << std::endl;
//         std::cout << "Actual X[" << i << "]: " << actualX << std::endl;

//         std::cout << "Particle " << i << ": " << std::endl;
//         std::cout << *it << std::endl;

//         if (std::abs(expectedX[0] - actualX[0]) > 1e-6 ||
//             std::abs(expectedX[1] - actualX[1]) > 1e-6 ||
//             std::abs(expectedX[2] - actualX[2]) > 1e-6) {
//             result = false;
//         }
//         ++it;
//     }
//     return result;
// }

// void CalculatorTest::runTest() {
//     std::cout << "Running calculation test with " << std::endl;
//     initializeParticlesForTest();
//     runSimulation(5.0, 0.1);
//     if (checkPositions()) {
//         std::cout << "PASS: Calculation ran as expected." << std::endl;
//     } else {
//         std::cout << "FAIL: Calculation did not run as expected." << std::endl;
//     }
// }

