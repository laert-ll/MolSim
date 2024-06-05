//
// Created by houj on 5/23/24.
//
#pragma once

#include "BoundaryHandler.h"
#include "calculators/Calculator.h"

namespace boundaries {
    /**
     * @class BoundaryController
     * @brief Controls the boundary handling for particles in a simulation domain.
     */
    class BoundaryController {
    public:
        /**
         * @brief Constructor for BoundaryController with 2D domain parameter.
         *
         * @param boundaryMap A map defining the boundary types for each direction.
         * @param calculator Pointer to the calculator used for force calculations.
         * @param domain The 2D domain size.
         * @param sigma The interaction distance parameter.
         */
        BoundaryController(const std::map<BoundaryDirection, BoundaryType>& boundaryMap,
                           calculators::Calculator *calculator, std::array<double, 2> domain, double sigma);

        /**
          * @brief Processes boundaries before the main particle calculations.
          *
          * @param container The particle container holding all particles.
          */
        void preProcessBoundaries(ParticleContainer &container) const;

        /**
         * @brief Processes boundaries after the main particle calculations.
         *
         * @param container The particle container holding all particles.
         */
        void postProcessBoundaries(ParticleContainer &container) const;

    private:
        const BoundaryHandler handler;
    };

}//boundaries