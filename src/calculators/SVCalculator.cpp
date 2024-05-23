#include "SVCalculator.h"
#include "../utils/ArrayUtils.h"

#include <cmath>

namespace calculators {

    void SVCalculator::calculate(ParticleContainer &particleContainer, double delta_t) {
        calculateX(particleContainer, delta_t);
        calculateF(particleContainer);
        calculateV(particleContainer, delta_t);
    }

    void SVCalculator::calculateF(ParticleContainer &particleContainer) {
        for (auto p = particleContainer.begin(); p != particleContainer.end(); ++p) {
            p->setOldF(p->getF());  // Update oldF with currentF
            p->setF({0, 0, 0});     // Reset F to zeros
        }

        // Iterate over all unique pairs of particles
        for (auto pair = particleContainer.pair_begin(); pair != particleContainer.pair_end(); ++pair) {
            // Get both particles
            Particle& particle1 = pair->first.get();
            Particle& particle2 = pair->second.get();

            // Get the positions and masses of the two particles
            const std::array<double, 3> x1 = particle1.getX();
            const std::array<double, 3> x2 = particle2.getX();

            const double m1 = particle1.getM();
            const double m2 = particle2.getM();

            // Calculate the distance vector and its norm
            const std::array<double, 3> dx = ArrayUtils::elementWisePairOp(x2, x1, std::minus<>());
            const double distance = ArrayUtils::L2Norm(dx);

            // Calculate the force between the two particles
            const double scalar = (m1 * m2) / std::pow(distance, 3);
            const std::array<double, 3> force = ArrayUtils::elementWiseScalarOp(scalar, dx, std::multiplies<>());

            // Add the force to the first particle and subtract it from the second particle (Newton's Third Law)
            const std::array<double, 3> newF1 = ArrayUtils::elementWisePairOp(particle1.getF(), force, std::plus<>());
            const std::array<double, 3> newF2 = ArrayUtils::elementWisePairOp(particle2.getF(), force, std::minus<>());
            particle1.setF(newF1);
            particle2.setF(newF2);
        }
    }
}

