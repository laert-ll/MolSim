//
// Created by Ujin on 04.05.2024.
//

#include "LJCalculator.h"

#include <cmath>
#include <omp.h>

namespace calculators {

    void LJCalculator::calculateFPairwise(Particle &particle1, Particle &particle2) const {
        // Get the positions and masses of the two particles
        const std::array<double, 3> x1 = particle1.getX();
        const std::array<double, 3> x2 = particle2.getX();

        if (isFar(x1, x2, threshold))
            return;

        // Calculate the distance vector and its norm
        const std::array<double, 3> dx = ArrayUtils::elementWisePairOp(x1, x2, std::minus<>());
        const double distance = ArrayUtils::L2Norm(dx);
        if (distance == 0.0)
            return;

        double epsilon = pow((particle1.getEpsilon() * particle2.getEpsilon()), 0.5);
        double sigma = 0.5 * (particle1.getSigma() + particle2.getSigma());
        // Calculate the force between the two particles
        const double forceMagnitude = -(24 * epsilon / (distance * distance)) *
                                      ((pow(sigma / distance, 6) - 2 * pow(sigma / distance, 12)));
        std::array<double, 3> force = ArrayUtils::elementWiseScalarOp(forceMagnitude, dx,
                                                                      std::multiplies<>());
        // Limitation of Force so they don't move too quickly
        for (int i = 0; i < 3; i++) {
            double f = force[i];
            if (f > 20000)
                force[i] = 20000;
            if (f < -20000)
                force[i] = -20000;
        }
        // Add the force to the first particle and subtract it from the second particle (Newton's Third Law)
        const std::array<double, 3> newF1 = ArrayUtils::elementWisePairOp(particle1.getF(), force,
                                                                          std::plus<>());
        const std::array<double, 3> newF2 = ArrayUtils::elementWisePairOp(particle2.getF(), force,
                                                                          std::minus<>());
        particle1.setF(newF1);
        particle2.setF(newF2);
    }
}