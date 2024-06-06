#include "LCCalculator.h"
#include <cmath>
#include <array>
#include <vector>

namespace calculators {

    void LCCalculator::calculateF(ParticleContainer &particleContainer) {
        for (auto & p : particleContainer) {
            p.setOldF(p.getF());  // Update oldF with currentF
            p.setF({0, 0, 0});     // Reset F to zeros
        }

        // assigns particles to their rightfull cells according to their position
        particleContainer.arrangeCells();

        for (auto p1 = particleContainer.begin(); p1 != particleContainer.end(); ++p1) {
            for (auto p2 : particleContainer.getNeighboringParticles(*p1)) {
                auto& particle1 = *p1;
                auto& particle2 = p2.get();
                // size_t index1 = std::distance(particleContainer.begin(), p1);
                // size_t index2 = std::distance(particleContainer.begin(), p2.get());
                // if (index1 > index2) {
                    // Get the positions and masses of the two particles
                    const std::array<double, 3>& x1 = particle1.getX();
                    const std::array<double, 3>& x2 = particle2.getX();
                    // Calculate the distance vector and its norm
                    const std::array<double, 3> dx = ArrayUtils::elementWisePairOp(x1, x2, std::minus<>());
                    const double distance = ArrayUtils::L2Norm(dx);

                    // Calculate the force between the two particles
                    const double forceMagnitude = -(24 * epsilon / (distance * distance)) *
                                                ((pow(sigma / distance, 6) - 2 * pow(sigma / distance, 12)));
                    std::array<double, 3> force = ArrayUtils::elementWiseScalarOp(forceMagnitude, dx,
                                                                                std::multiplies<>());

                    // Add the force to the first particle and subtract it from the second particle (Newton's Third Law)
                    const std::array<double, 3> newF1 = ArrayUtils::elementWisePairOp(particle1.getF(), force,
                                                                                    std::plus<>());
                    const std::array<double, 3> newF2 = ArrayUtils::elementWisePairOp(particle2.getF(), force,
                                                                                    std::minus<>());
                    particle1.setF(newF1);
                    particle2.setF(newF2);
                // }
            }
        }
    }
}
