//
// Created by Ujin on 05.05.2024.
//

#include "LJCalculatorTest.h"
template<typename T, std::size_t N>
std::ostream &operator<<(std::ostream &os, const std::array<T, N> &arr) {
    std::copy(arr.cbegin(), arr.cend(), std::ostream_iterator<T>(os, " "));
    return os;
}

void LJCalculatorTest::initializeParticlesForTest() {
    particleContainer.addParticle(Particle({1, 1, 1}, {0, 0, 0}, 1.0, 0.0));
    particleContainer.addParticle(Particle({-1, -1, -1}, {0, 0, 0}, 1.0, 0.0));
    particleContainer.initializePairs();
    particleContainer.setVolumes();
}

bool LJCalculatorTest::checkPositions() {
    bool result = true;
    std::vector<std::array<double, 3>> expectedPositions = {
            {0.0478651,  0.0478651,  0.0478651},
            {-0.0478651, -0.0478651, -0.0478651}
    };

    auto it = particleContainer.begin();
    for (size_t i = 0; i < particleContainer.getSize(); ++i) {
        std::array<double, 3> expectedX = expectedPositions[i];
        std::array<double, 3> actualX = it->getX();

        std::cout << "Expected X[" << i << "]: " << expectedX << std::endl;
        std::cout << "Actual X[" << i << "]: " << actualX << std::endl;

        std::cout << "Particle " << i << ": " << std::endl;
        std::cout << *it << std::endl;

        if (std::abs(expectedX[0] - actualX[0]) > 1e-6 ||
            std::abs(expectedX[1] - actualX[1]) > 1e-6 ||
            std::abs(expectedX[2] - actualX[2]) > 1e-6) {
            result = false;
        }
        it++;
    }
    return result;
}