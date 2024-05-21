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
        const double sigma;
        const double epsilon;
        const double threshold;

    public:
        /**
         * Default constructor for the SVCalculator class.
         *
         * Initializes the SVCalculator object.
         */
        LJCalculator(double sigma, double epsilon, double threshold) : sigma(sigma), epsilon(epsilon), threshold(threshold) {}

        /**
             * Calculates the force between all pairs of unique particles considering the third Newton's law.
             *
             * @param particleContainer The ParticleContainer containing the particles to calculate the forces for.
             */
        void calculateF(ParticleContainer &particleContainer) override;

        void calculateReflection(Particle &p, Particle &ghost) override;
    };
}
