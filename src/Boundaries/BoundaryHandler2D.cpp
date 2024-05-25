//
// Created by houj on 5/23/24.
//

#include "BoundaryHandler2D.h"

namespace boundaries {

    void BoundaryHandler2D::handleBoundary(ParticleContainer &container) {
        double boundary = 45;
        double tolerance = 1.12246204831;
        for (auto &p : container) {
            double distanceToBoundary = boundary - p.getX().at(0);
            // only calculate reflection if near boundary
            if (distanceToBoundary < tolerance) {
                Particle ghost{p};
                ghost.setX({boundary + distanceToBoundary, p.getX().at(1), p.getX().at(2)});
                calculator->calculateFpair(p, ghost);
            }
        }
    }

    void BoundaryHandler2D::handleReflection(ParticleContainer &container, int index) {
        //if selected index is lower boundary (lowerX, lowerY, lowerZ)
        if (index <= 2) {
            double boundary = boundaryPositions[index];
            double tolerance = 1.12246204831 * sigma;
        }
    }

    BoundaryHandler2D::BoundaryHandler2D(std::vector<BoundaryType> boundaryTypes, std::vector<double> boundaryPositions, std::unique_ptr<calculators::Calculator> &calculator)
            : boundaryTypes(std::move(boundaryTypes)), boundaryPositions(std::move(boundaryPositions)), calculator(std::move(calculator)) {
    }

    void BoundaryHandler2D::setBoundary(BoundaryDirection direction, BoundaryType type) {
        boundaryTypes[static_cast<int>(direction)] = type;
    }

    BoundaryType BoundaryHandler2D::getBoundary(BoundaryDirection direction) const {
        return boundaryTypes[static_cast<int>(direction)];
        }


}