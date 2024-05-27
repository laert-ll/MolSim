//
// Created by houj on 5/23/24.
//
#pragma once

#include "BoundaryHandler2D.h"
#include "calculators/Calculator.h"

namespace boundaries {
    class BoundaryController {
    public:
//        BoundaryController() = default;

        BoundaryController(const std::map<BoundaryDirection, BoundaryType>& boundaryMap,
                           std::unique_ptr<calculators::Calculator> &calculator, std::array<double, 2> domain, double sigma);

        void handleBoundaries(ParticleContainer &container);
    private:
        const BoundaryHandler2D handler;
    };
    //Konstruktor mit Grenze-Parameter

}//boundaries