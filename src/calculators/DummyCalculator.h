//
// Created by kimj2 on 01.05.2024.
//

#pragma once

#include "../objects/ParticleContainer.h"
#include "Calculator.h"

namespace calculators {
    /**
     * @class DummyCalculator
     * @brief Concrete calculator class that does nothing.
     *
     * This class is a placeholder for a calculator that does not perform any actual calculations
     * and only exists to test the strategy pattern of calculators.
     * It inherits from the `Calculator` base class and provides empty implementations for the `calculate`, `calculateX`, `calculateF`, and `calculateV` methods.
     */
    class DummyCalculator : public Calculator {
    public:
        DummyCalculator() = default;

        /**
         *
         * This method is a dummy method and does nothing.
         *
         * @param particleContainer The container of particles to perform the calculations on.
         * @param delta_t The time step used for the calculations.
         */
        void calculate(ParticleContainer &particleContainer, double delta_t);

    private:
        /**
         *
         * This method is a dummy method and does nothing.
         *
         * @param particleContainer The container of particles to calculate the forces for.
         */
        void calculateF(ParticleContainer &particleContainer);

        /**
         *
         * This method is a dummy method and does nothing.
         *
         * @param particleContainer The container of particles to update the positions of.
         * @param delta_t The time step used for the calculations.
         */
        void calculateX(ParticleContainer &particleContainer, double delta_t);

        /**
         * @brief Calculates the new velocities of particles.
         *
         * This method is a placeholder and does nothing. It is intended to be overridden by derived classes to provide actual velocity calculation logic.
         *
         * @param particleContainer The container of particles to update the velocities of.
         * @param delta_t The time step used for the calculations.
         */
        void calculateV(ParticleContainer &particleContainer, double delta_t);
    };
}