//
// Created by Ujin on 04.05.2024.
//
#pragma once

#include "../objects/ParticleContainer.h"
#include "Calculator.h"

#ifndef PSEMOLDYN_GROUPC_LJCALCULATOR_H
#define PSEMOLDYN_GROUPC_LJCALCULATOR_H

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
        double sigma = 1; //TODO: How will those parameters be set?
        double epsilon = 5;
        /**
         * Calculates the new position for all particles using the Stoermer-Verlet method.
         *
         * @param particleContainer The ParticleContainer containing the particles to update.
         * @param delta_t The time step used in the calculations.
         */
        void calculateX(ParticleContainer &particleContainer, double delta_t);

        /**
         * Calculates the force between all pairs of unique particles considering the third Newton's law.
         *
         * @param particleContainer The ParticleContainer containing the particles to calculate the forces for.
         */
        void calculateF(ParticleContainer &particleContainer);

        /**
         * Calculates the velocity for all particles using the Stoermer-Verlet method.
         *
         * @param particleContainer The ParticleContainer containing the particles to update.
         * @param delta_t The time step used in the calculations.
         */
        void calculateV(ParticleContainer &particleContainer, double delta_t);



    public:
        /**
         * Default constructor for the SVCalculator class.
         *
         * Initializes the SVCalculator object.
         */
        LJCalculator() = default;

        /**
         * Calls methods to calculate positions, forces, and velocities of particles in the right order.
         *
         * @param particleContainer The ParticleContainer containing the particles to update.
         * @param delta_t The time step used in the calculations.
         */
        void calculate(ParticleContainer &particleContainer, double delta_t);

        //For Later, where we may need to change Epsilon/Sigma - or is it particle
        void setEpsilon(double e) {
            epsilon = e;
        }
        void setSigma(double s) {
            sigma = s;
        }
        double getEpsilon() {
            return epsilon;
        }
        double getSigma() {
            return sigma;
        }
    };
}
#endif //PSEMOLDYN_GROUPC_LJCALCULATOR_H
