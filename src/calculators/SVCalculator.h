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
    class SVCalculator : public Calculator {

    public:
        /**
         * Default constructor for the SVCalculator class.
         *
         * Initializes the SVCalculator object.
         */
        SVCalculator() = default;

        /**
         * Calls methods to calculate positions, forces, and velocities of particles in the right order.
         *
         * @param particleContainer The ParticleContainer containing the particles to update.
         * @param delta_t The time step used in the calculations.
         */
//        void calculate(ParticleContainer &particleContainer, double delta_t) override;

        /**
             * Calculates the force between all pairs of unique particles considering the third Newton's law.
             *
             * @param particleContainer The ParticleContainer containing the particles to calculate the forces for.
             */
//        void calculateF(ParticleContainer &particleContainer) override;

//        void calculateReflection(Particle &p, Particle &ghost) override;
        void calculateFPairwise(Particle &particle1, Particle &particle2) const override;

        void calculateLC(LinkedCellContainer &linkedCellContainer, double delta_t) override {
        // Implementation of the calculateLC function
        }
    };
}