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
            // Get the positions and masses of the two particles
            std::array<double, 3> x1 = pair->first.get().getX();
            std::array<double, 3> x2 = pair->second.get().getX();

            // Calculate the distance vector and its norm
            std::array<double, 3> dx = {x2[0] - x1[0], x2[1] - x1[1], x2[2] - x1[2]};
            double distance = std::sqrt(dx[0] * dx[0] + dx[1] * dx[1] + dx[2] * dx[2]);

            // Calculate the force between the two particles
            double distanceSquared = distance * distance;
            double forceMagnitude = -24 * epsilon / distanceSquared * (pow(sigma / distance, 6) - 2 * pow(sigma / distance, 12));
            std::array<double, 3> force = {forceMagnitude * dx[0], forceMagnitude * dx[1], forceMagnitude * dx[2]};

            // Add the force to the first particle and subtract it from the second particle (Newton's Third Law)
            std::array<double, 3> f1 = pair->first.get().getF();
            std::array<double, 3> f2 = pair->second.get().getF();
            pair->first.get().setF({f1[0] + force[0], f1[1] + force[1], f1[2] + force[2]});
            pair->second.get().setF({f2[0] - force[0], f2[1] - force[1], f2[2] - force[2]});
        }
    }
}


