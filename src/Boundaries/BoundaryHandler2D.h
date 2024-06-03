//
// Created by houj on 5/23/24.
//

#pragma once

#include <vector>
#include "BoundaryEnums.h"
#include "BoundaryProperties.h"
#include "../objects/ParticleContainer.h"
#include "calculators/Calculator.h"

namespace boundaries {
    /**
     * @class BoundaryHandler2D
     * @brief Handles boundary conditions for a 2D simulation domain.
     */
    class BoundaryHandler2D{
    public:
        /**
         * @brief Constructor for BoundaryHandler2D.
         *
         * @param properties The boundary properties.
         * @param calculator Pointer to the calculator used for force calculations.
         * @param sigma The interaction distance parameter.
         */
        BoundaryHandler2D(BoundaryProperties properties, calculators::Calculator *calculator, double sigma);

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

    private:
        const BoundaryProperties properties;
        const double sigma=1;
        const calculators::Calculator* calculator;
        };
};