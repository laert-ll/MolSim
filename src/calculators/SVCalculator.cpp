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
            const std::array<double, 3> dx = ArrayUtils::elementWisePairOp(x2, x1, std::minus<double>());
            const double distance = ArrayUtils::L2Norm(dx);

            // Calculate the force between the two particles
            const double scalar = (m1 * m2) / std::pow(distance, 3);
            const std::array<double, 3> force = ArrayUtils::elementWiseScalarOp(scalar, dx, std::multiplies<double>());


            // Add the force to the first particle and subtract it from the second particle (Newton's Third Law)
            const std::array<double, 3> newF1 = ArrayUtils::elementWisePairOp(particle1.getF(), force, std::plus<double>());
            const std::array<double, 3> newF2 = ArrayUtils::elementWisePairOp(particle2.getF(), force, std::minus<double>());
            particle1.setF(newF1);
            particle2.setF(newF2);
        }
    }

    void SVCalculator::calculateX(ParticleContainer &particleContainer, double delta_t) {
        for (auto p = particleContainer.begin(); p != particleContainer.end(); ++p) {
            // Get the current position, velocity, force and mass of the particle
            std::array<double, 3> x = p->getX();
            const std::array<double, 3> v = p->getV();
            const std::array<double, 3> f = p->getF();

            const double m = p->getM();

            // Calculate the acceleration
            const std::array<double, 3> a = ArrayUtils::elementWiseScalarOp(1.0 / m, f, std::multiplies<double>());


            // Update the particles new position using the Velocity-Störmer-Verlet method
            const std::array<double, 3> v_summand = ArrayUtils::elementWiseScalarOp(delta_t, v, std::multiplies<double>());
            const std::array<double, 3> a_summand = ArrayUtils::elementWiseScalarOp((delta_t * delta_t / 2), a, std::multiplies<double>());
            // Combine v_summand and a_summand into a single summand
            const std::array<double, 3> summand = ArrayUtils::elementWisePairOp(v_summand, a_summand, std::plus<double>());

            x = ArrayUtils::elementWisePairOp(x, summand, std::plus<double>());

            p->setX(x);
        }
    }

    void SVCalculator::calculateV(ParticleContainer &particleContainer, double delta_t) {
        for (auto p = particleContainer.begin(); p != particleContainer.end(); ++p) {
            // Get the current position, velocity, force and mass of the particle
            std::array<double, 3> v = p->getV();
            const std::array<double, 3> f = p->getF();
            const std::array<double, 3> old_f = p->getOldF();
            const double m = p->getM();

            // Calculate the average force
            std::array<double, 3> avg_f = ArrayUtils::elementWisePairOp(
                    f, old_f,
                    [](double a, double b) { return (a + b) / 2.0; } // Lambda function to calculate average
            );

            // Update the particles new velocity using the Velocity-Störmer-Verlet method
            const std::array<double, 3> delta_v = ArrayUtils::elementWiseScalarOp(delta_t / m, avg_f, std::multiplies<double>());
            v = ArrayUtils::elementWisePairOp(v, delta_v, std::plus<double>());
            p->setV(v);
        }
    }
}

