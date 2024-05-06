//
// Created by Ujin on 04.05.2024.
//
#pragma once

#include "../objects/ParticleContainer.h"
#include "Calculator.h"

namespace calculators {
    /**
     * @class SVCalculator
     * @brief A class responsible for performing calculations related to particles.
     *
     * This class provides methods to calculate the new position, force, and velocity of particles,
     * as well as to plot the particles to a VTK file. It uses the Stoermer-Verlet method for the calculations.
     */
    class LJCalculator : public Calculator {
    private:
        double sigma = 1;
        double epsilon = 5;

        /**
         * Calculates the force between all pairs of unique particles considering the third Newton's law.
         *
         * @param particleContainer The ParticleContainer containing the particles to calculate the forces for.
         */
        void calculateF(ParticleContainer &particleContainer) override;

    public:
        /**
         * Default constructor for the SVCalculator class.
         *
         * Initializes the SVCalculator object.
         */
        LJCalculator(double sigma, double epsilon) : sigma(sigma), epsilon(epsilon) {}

    };
}
