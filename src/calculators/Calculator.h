//
// Created by kimj2 on 01.05.2024.
//

#pragma once

#include "../objects/ParticleContainer.h"

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

    private:
        /**
         * @brief Calculates the forces acting on particles.
         *
         * This method is responsible for calculating the forces acting on all particles in the provided particle container.
         *
         * @param particleContainer The container of particles to calculate the forces for.
         */
        virtual void calculateF(ParticleContainer &particleContainer) = 0;

    protected:
        /**
         * @brief Calculates the new velocities of particles.
         *
         * This method is responsible for updating the velocities of all particles in the provided particle container.
         *
         * @param particleContainer The container of particles to update the velocities of.
         * @param delta_t The time step used for the calculations.
         */
        virtual void calculateV(ParticleContainer &particleContainer, double delta_t) {
            for (auto &p: particleContainer) {
                // Get the current position, velocity, force and mass of the particle
                std::array<double, 3> v = p.getV();
                std::array<double, 3> f = p.getF();
                std::array<double, 3> old_f = p.getOldF();
                double m = p.getM();

                // Calculate the average force
                std::array<double, 3> avg_f = {(f[0] + old_f[0]) / 2, (f[1] + old_f[1]) / 2, (f[2] + old_f[2]) / 2};

                // Update the particles new velocity using the Velocity-Störmer-Verlet method
                v[0] += (delta_t * avg_f[0]) / m;
                v[1] += (delta_t * avg_f[1]) / m;
                v[2] += (delta_t * avg_f[2]) / m;

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
            for (auto &p: particleContainer) {
                // Get the current position, velocity, force and mass of the particle
                std::array<double, 3> x = p.getX();
                std::array<double, 3> v = p.getV();
                std::array<double, 3> f = p.getF();

                double m = p.getM();

                // Calculate the acceleration
                std::array<double, 3> a = {f[0] / m, f[1] / m, f[2] / m};

                // Update the particles new position using the Velocity-Störmer-Verlet method
                x[0] += delta_t * v[0] + (delta_t * delta_t / 2) * a[0];
                x[1] += delta_t * v[1] + (delta_t * delta_t / 2) * a[1];
                x[2] += delta_t * v[2] + (delta_t * delta_t / 2) * a[2];

                p.setX(x);
            }
        }
    };
}