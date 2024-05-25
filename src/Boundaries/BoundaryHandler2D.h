//
// Created by houj on 5/23/24.
//

#pragma once

#include <vector>
#include "BoundaryEnums.h"
#include "../objects/ParticleContainer.h"
#include "calculators/Calculator.h"

namespace boundaries {
    class BoundaryHandler2D{
    public:
        BoundaryHandler2D() = default;

        BoundaryHandler2D(std::vector<BoundaryType> boundaryTypes, std::vector<double>, std::unique_ptr<calculators::Calculator> &calculator);

        void setBoundary(BoundaryDirection direction, BoundaryType type);

        BoundaryType getBoundary(BoundaryDirection direction) const;

        void handleBoundary(ParticleContainer &container);

        void handleReflection(ParticleContainer &container, int index);

    private:
        // This vector should have the size of 4, storing the boundaries in the following order:
        // [0] = top, [1] = right, [2] = bottom, [3] = left
        // possible values: BoundaryDirection:: REFLECTED, OUTFLOW, OFF
        std::vector<BoundaryType> boundaryTypes;
        // This vector contains the boundaryPositions in the following order:
        // lowerX, lowerY, lowerZ, higherX, higherY, higherZ
        std::vector<double> boundaryPositions;

        double sigma=1;

        std::unique_ptr<calculators::Calculator> calculator;
    };

};