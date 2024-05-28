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
    class BoundaryHandler2D{
    public:
//        BoundaryHandler2D() = default;

        BoundaryHandler2D(BoundaryProperties properties, calculators::Calculator& calculator, double sigma);

        void handleBoundary(ParticleContainer &container) const;

        void handleReflection(ParticleContainer &container, BoundaryDirection direction) const;

        void handleOutflow(ParticleContainer &container, BoundaryDirection direction) const;

//        const BoundaryProperties &getProperties() const;
//
//        const double getSigma() const;
//
//        const std::unique_ptr<calculators::Calculator> &getCalculator() const;

    private:
        const BoundaryProperties properties;

        const double sigma=1;

        const std::unique_ptr<calculators::Calculator> calculator;
        };
};