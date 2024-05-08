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
        virtual void calculate(ParticleContainer &particleContainer, double delta_t) {}

    private:
        /**
         * @brief Calculates the forces acting on particles.
         *
         * This method is responsible for calculating the forces acting on all particles in the provided particle container.
         *
         * @param particleContainer The container of particles to calculate the forces for.
         */
        virtual void calculateF(ParticleContainer &particleContainer) {}

        /**
         * @brief Calculates the new positions of particles.
         *
         * This method is responsible for updating the positions of all particles in the provided particle container.
         *
         * @param particleContainer The container of particles to update the positions of.
         * @param delta_t The time step used for the calculations.
         */
        virtual void calculateX(ParticleContainer &particleContainer, double delta_t) {}

        /**
         * @brief Calculates the new velocities of particles.
         *
         * This method is responsible for updating the velocities of all particles in the provided particle container.
         *
         * @param particleContainer The container of particles to update the velocities of.
         * @param delta_t The time step used for the calculations.
         */
        virtual void calculateV(ParticleContainer &particleContainer, double delta_t) {}
    };
}