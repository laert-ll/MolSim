//
// Created by kimj2 on 01.05.2024.
//

#pragma once

#include "../objects/ParticleContainer.h"
#include "../utils/ArrayUtils.h"
#include "/opt/homebrew/opt/libomp/include/omp.h"

namespace calculators {
    /**
     * @class Calculator
     * @brief Abstract base class for calculators that perform physics calculations on particles.
     *
     * This class defines the interface for calculators that perform various physics calculations on particles.
     * It is designed to be subclassed by specific calculator implementations.
     */
    class Calculator {
    public:
        Calculator() = default;

        virtual ~Calculator() = default;

        /**
         * @brief Performs the main calculation on the particles in the container.
         *
         * This method is responsible for coordinating the calculation of forces (`calculateF`), new positions (`calculateX`),
         * and velocities (`calculateV`) for all particles in the provided particle container.
         *
         * @param particleContainer The container of particles to perform the calculations on.
         * @param delta_t The time step used for the calculations.
         */
        virtual void calculate(ParticleContainer &particleContainer, double delta_t) {
            calculateF(particleContainer);
            calculateX(particleContainer, delta_t);
            calculateV(particleContainer, delta_t);
        }

        /**
         * @brief Calculates the forces acting on particles.
         *
         * This method is responsible for calculating the forces acting on all particles in the provided particle container.
         *
         * @param particleContainer The container of particles to calculate the forces for.
         */
        virtual void calculateF(ParticleContainer &particleContainer) {
            // #pragma omp parallel for
            for (auto &p: particleContainer) {
                p.setOldF(p.getF());  // Update oldF with currentF
                p.setF({0, 0, 0});     // Reset F to zeros
            }

            // Iterate over all unique pairs of particles
            // #pragma omp parallel for
            for (auto pair = particleContainer.pair_begin(); pair != particleContainer.pair_end(); ++pair) {
                Particle &particle1 = pair->first.get();
                Particle &particle2 = pair->second.get();
                calculateFpair(particle1, particle2);
            }
        }

        /**
             * @brief Calculates the new velocities of particles.
             *
             * This method is responsible for updating the velocities of all particles in the provided particle container.
             *
             * @param particleContainer The container of particles to update the velocities of.
             * @param delta_t The time step used for the calculations.
             */
        virtual void calculateV(ParticleContainer &particleContainer, double delta_t) {
            #pragma omp parallel for
            for (auto &p: particleContainer) {
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

        /**
             * @brief Calculates the new positions of particles.
             *
             * This method is responsible for updating the positions of all particles in the provided particle container.
             *
             * @param particleContainer The container of particles to update the positions of.
             * @param delta_t The time step used for the calculations.
             */
        virtual void calculateX(ParticleContainer &particleContainer, double delta_t) {
            #pragma omp parallel for
            for (auto &p: particleContainer) {
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

        virtual void calculateFpair(Particle &particle1, Particle &particle2) const {};

    protected:
        /**
         * @brief Determines if two points are far apart based on a given threshold.
         *
         * This function calculates the Manhattan  distance
         * and then checks if it exceeds the given threshold. If the distance is greater than
         * the threshold, the function returns true, indicating that the points are considered "far".
         *
         * @param x1 The first point represented as an array of three doubles.
         * @param x2 The second point represented as an array of three doubles.
         * @param threshold The threshold value to compare the Manhattan  distance with.
         * @return True if the points are considered "far", false otherwise.
         */
        virtual bool isFar(const std::array<double, 3> &x1, const std::array<double, 3> &x2, double threshold) {
            const std::array<double, 3> absDiff = ArrayUtils::elementWisePairOp(x1, x2,
                                                                                [](double a, double b) {
                                                                                    return std::abs(a - b);
                                                                                });
            const double sum = std::accumulate(absDiff.begin(), absDiff.end(), 0.0);

            return sum > threshold;
        }

    private:
        };
    };