#include "LC_LJCalculator.h"
#include "spdlog/spdlog.h"

namespace calculators {

    void LC_LJCalculator::calculateLC(LinkedCellContainer &linkedCellContainer, double delta_t) {
        calculateLC_F(linkedCellContainer);
        calculateLC_X(linkedCellContainer, delta_t);
        calculateLC_V(linkedCellContainer, delta_t);
    }

    void LC_LJCalculator::calculateLC_F(LinkedCellContainer &linkedCellContainer) {
        for (auto &p: linkedCellContainer) {
            p.setOldF(p.getF());  // Update oldF with currentF
            p.setF({0, 0, 0});     // Reset F to zeros
        }

        for (Particle &particle1: linkedCellContainer) {
            std::array<double, 3> x1 = particle1.getX();
            // SPDLOG_INFO("Processing Particle at position ({}, {}, {})", x1[0], x1[1], x1[2]);
            std::vector<std::shared_ptr<Cell>> &neighboringCells = linkedCellContainer.getNeighboringCellsIncludingSelf(particle1);
            for (auto &cell : neighboringCells) {
                // SPDLOG_INFO("Processing Cell at index ({}, {}, {})", cell->getIndex()[0], cell->getIndex()[1],
                //           cell->getIndex()[2]);
                for (std::shared_ptr<Particle> p2 : cell.get()->getParticles()) {
                    auto &particle2 = *p2;

                    // LJ force calculation
                    const std::array<double, 3> x2 = particle2.getX();

                    // Calculate the distance vector and its norm
                    const std::array<double, 3> dx = ArrayUtils::elementWisePairOp(x1, x2, std::minus<>());
                    const double distance = ArrayUtils::L2Norm(dx);

                    double epsilon = pow((particle1.getEpsilon() * particle2.getEpsilon()), 0.5);
                    double sigma = 0.5 * (particle1.getSigma() + particle2.getSigma());
                    // Calculate the force between the two particles
                    const double forceMagnitude = -(24 * epsilon / (distance * distance)) *
                                                ((pow(sigma / distance, 6) - 2 * pow(sigma / distance, 12)));

                    std::array<double, 3> force = ArrayUtils::elementWiseScalarOp(forceMagnitude, dx, std::multiplies<>());

                    // Add the force to the first particle and subtract it from the second particle (Newton's Third Law)
                    const std::array<double, 3> newF1 = ArrayUtils::elementWisePairOp(particle1.getF(), force,
                                                                                    std::plus<>());
                    const std::array<double, 3> newF2 = ArrayUtils::elementWisePairOp(particle2.getF(), force,
                                                                                    std::minus<>());
                    particle1.setF(newF1);
                    particle2.setF(newF2);
                }
            }
        }
    }

    void LC_LJCalculator::calculateLC_X(LinkedCellContainer &linkedCellContainer, double delta_t) {
            for (auto &p: linkedCellContainer) {
                // Get the current position, velocity, force and mass of the particle
                std::array<double, 3> x = p.getX();
                const std::array<double, 3> v = p.getV();
                const std::array<double, 3> f = p.getF();

                const double m = p.getM();

                // Calculate the acceleration
                const std::array<double, 3> a = ArrayUtils::elementWiseScalarOp(1.0 / m, f, std::multiplies<>());


                // Update the particles new position using the Velocity-Störmer-Verlet method
                const std::array<double, 3> v_summand = ArrayUtils::elementWiseScalarOp(delta_t, v,
                                                                                        std::multiplies<>());
                const std::array<double, 3> a_summand = ArrayUtils::elementWiseScalarOp((delta_t * delta_t / 2), a,
                                                                                        std::multiplies<>());
                // Combine v_summand and a_summand into a single summand
                const std::array<double, 3> summand = ArrayUtils::elementWisePairOp(v_summand, a_summand,
                                                                                    std::plus<>());

                x = ArrayUtils::elementWisePairOp(x, summand, std::plus<>());

                p.setX(x);
            }
    }

    void LC_LJCalculator::calculateLC_V(LinkedCellContainer &linkedCellContainer, double delta_t) {
        for (auto &p: linkedCellContainer) {
            // Get the current position, velocity, force and mass of the particle
            std::array<double, 3> v = p.getV();
            const std::array<double, 3> f = p.getF();
            const std::array<double, 3> old_f = p.getOldF();
            const double m = p.getM();

            // Calculate the average force
            std::array<double, 3> avg_f = ArrayUtils::elementWisePairOp(
                    f, old_f,
                    [](double a, double b) { return (a + b) / 2.0; } // Lambda function to calculate average
            );

            // Update the particles new velocity using the Velocity-Störmer-Verlet method
            const std::array<double, 3> delta_v = ArrayUtils::elementWiseScalarOp(delta_t / m, avg_f,
                                                                                    std::multiplies<>());
            v = ArrayUtils::elementWisePairOp(v, delta_v, std::plus<>());

            p.setV(v);
        }
    }
}
