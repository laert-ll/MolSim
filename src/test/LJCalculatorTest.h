//
// Created by Ujin on 05.05.2024.
//

#ifndef MOLSIM_LJCALCULATORTEST_H
#define MOLSIM_LJCALCULATORTEST_H

#include <memory>
#include "calculators/Calculator.h"
#include <iterator>
#include <iostream>
//#include "gtest/gtest.h"

class LJCalculatorTest {
    private:
        /**
         * @brief The container for particles used in the test.
         */
        ParticleContainer particleContainer;

        /**
        * @brief The time step used in the simulation.
        */
        double timeStep;

        /**
        * @brief The calculator object used for the simulation.
        */
        std::unique_ptr<calculators::Calculator> calculator;

        /**
        * @brief Initializes the particles for the test.
        *
        * This function should initialize the particles in the particle container with the test values.
        */
        void initializeParticlesForTest();

    /**
 * @brief Checks the positions of the particles.
 * @return True if the positions are as expected, false otherwise.
 *
 * This function should check the positions of the particles after the simulation and compare them to the expected values.
 */
    bool checkPositions();
};


#endif //MOLSIM_LJCALCULATORTEST_H
