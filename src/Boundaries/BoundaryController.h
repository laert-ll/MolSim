//
// Created by houj on 5/23/24.
//
#pragma once

#include "BoundaryHandler2D.h"
#include "calculators/Calculator.h"

namespace boundaries {
    class BoundaryController {
    public:
        BoundaryController() = default;
        BoundaryController(std::vector<BoundaryType> boundaryTypes, std::vector<double> boundaryPositions, std::unique_ptr<calculators::Calculator> &calculator);
        void handleBoundaries(ParticleContainer &container);
    private:
        BoundaryHandler2D handler{};

    };
    //Konstruktor mit Grenze-Parameter

}//boundaries