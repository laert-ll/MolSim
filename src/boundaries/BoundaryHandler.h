//
// Created by houj on 5/23/24.
//

#pragma once

#include <vector>
#include <gtest/gtest.h>

#include "BoundaryEnums.h"
#include "BoundaryProperties.h"
#include "../objects/ParticleContainer.h"
#include "calculators/Calculator.h"


namespace boundaries {
    /**
     * @class BoundaryHandler
     * @brief Handles boundary conditions for a 2D simulation domain.
     */
    class BoundaryHandler{
    public:
        /**
         * @brief Constructor for BoundaryHandler.
         *
         * @param properties The boundary properties.
         * @param calculator Pointer to the calculator used for force calculations.
         * @param sigma The interaction distance parameter.
         */
        BoundaryHandler(BoundaryProperties properties, calculators::Calculator *calculator, double sigma);

        /**
         * @brief Pre-processes boundaries before the main particle calculations.
         *
         * @param container The particle container holding all particles.
         */
        void preProcessBoundaries(ParticleContainer &container) const;
        /**
         * @brief Post-processes boundaries after the main particle calculations.
         *
         * @param container The particle container holding all particles.
         */
        void postProcessBoundaries(ParticleContainer &container) const;

    private:
        const BoundaryProperties properties;
        const double sigma=1;
        const calculators::Calculator* calculator;

        /**
         * @brief Handles reflection for particles near the reflecting boundary.
         *
         * @param container The particle container holding all particles.
         * @param direction The boundary direction to process.
         */
        void handleReflection(ParticleContainer &container, BoundaryDirection direction) const;
        /**
         * @brief Handles outflow for particles outside the domain.
         *
         * @param container The particle container holding all particles.
         * @param direction The boundary direction to process.
         */
        void handleOutflow(ParticleContainer &container, BoundaryDirection direction) const;
        /**
         * @brief Handles periodic for particles outside the domain.
         * For x-domain {0, 20} 0 will be included, 20 will be excluded -> [0, 20)
         *
         * @param container The particle container holding all particles.
         * @param direction The boundary direction to process.
         */
        void handlePeriodic(ParticleContainer &container, BoundaryDirection direction) const;

/**
 * Class section end
 *
 *
 *
 * --------------------------------------------TEST SECTION------------------------------------------------------------
 * To be able to use the private methods and attributes in testing, FRIEND_TESTs are declared here.
 */
        FRIEND_TEST(BoundaryHandlerTest, BasicReflection);
        FRIEND_TEST(BoundaryHandlerTest, CornerReflection);
        FRIEND_TEST(BoundaryHandlerTest, BasicOutflow);
        FRIEND_TEST(BoundaryHandlerTest, MixedBoundaries);
    };
};