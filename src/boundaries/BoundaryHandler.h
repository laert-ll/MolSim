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
         */
        BoundaryHandler(BoundaryProperties properties, std::shared_ptr<calculators::Calculator> calculator)
                : properties(std::move(properties)), calculator(std::move(calculator)) {}

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

        void preProcessBoundaries(LinkedCellContainer &linkedCellContainer) const;

        void postProcessBoundaries(LinkedCellContainer &linkedCellContainer) const;


    private:
        const BoundaryProperties properties;
        std::shared_ptr<calculators::Calculator> calculator;

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

        void handleReflection(LinkedCellContainer &linkedCellContainer, BoundaryDirection direction) const;

        void handleOutflow(LinkedCellContainer &linkedCellContainer, BoundaryDirection direction) const;

        void handlePeriodic(LinkedCellContainer &linkedCellContainer, BoundaryDirection direction) const;


        //---------------------------------------Helper methods---------------------------------------
        int retrieveRelevantPositionIndex(const BoundaryDirection &direction) const;

        bool retrieveIsLowerBound(const BoundaryDirection &direction) const;

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