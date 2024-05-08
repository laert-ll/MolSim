//
// Created by Ujin on 04.05.2024.
//

#include "LJCalculator.h"

#include <cmath>

namespace calculators {

    void LJCalculator::calculateF(ParticleContainer &particleContainer) {
        for (auto p = particleContainer.begin(); p != particleContainer.end(); ++p) {
            p->setOldF(p->getF());  // Update oldF with currentF
            p->setF({0, 0, 0});     // Reset F to zeros
        }

        // Iterate over all unique pairs of particles
        for (auto pair = particleContainer.pair_begin(); pair != particleContainer.pair_end(); ++pair) {
            // Get both particles
            Particle &particle1 = pair->first.get();
            Particle &particle2 = pair->second.get();

            // Get the positions and masses of the two particles
            const std::array<double, 3> x1 = particle1.getX();
            const std::array<double, 3> x2 = particle2.getX();

            // Calculate the distance vector and its norm
            const std::array<double, 3> dx = ArrayUtils::elementWisePairOp(x2, x1, std::minus<double>());
            const double distance = ArrayUtils::L2Norm(dx);

            // Calculate the force between the two particles
            const double forceMagnitude = -(24 * epsilon / (distance * distance)) *
                                          ((pow(sigma / distance, 6) - 2 * pow(sigma / distance, 12)));
            std::array<double, 3> force = ArrayUtils::elementWiseScalarOp(forceMagnitude, dx,
                                                                          std::multiplies<double>());

            // Add the force to the first particle and subtract it from the second particle (Newton's Third Law)
            const std::array<double, 3> newF1 = ArrayUtils::elementWisePairOp(particle1.getF(), force,
                                                                              std::plus<double>());
            const std::array<double, 3> newF2 = ArrayUtils::elementWisePairOp(particle2.getF(), force,
                                                                              std::minus<double>());
            particle1.setF(newF1);
            particle2.setF(newF2);
        }
    }
}


