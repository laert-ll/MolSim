#include "SVCalculator.h"
#include "../utils/ArrayUtils.h"

#include <cmath>

namespace calculators {

    void SVCalculator::calculateFpair(Particle &particle1, Particle &particle2) const {
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

