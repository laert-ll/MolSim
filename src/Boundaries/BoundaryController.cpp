//
// Created by houj on 5/23/24.
//

#include "BoundaryController.h"

namespace boundaries {
    BoundaryController::BoundaryController(std::vector<BoundaryType> boundaryTypes, std::vector<double> boundaryPositions, std::unique_ptr<calculators::Calculator> &calculator)
    : handler(std::move(boundaryTypes), std::move(boundaryPositions), calculator) {}

    void BoundaryController::handleBoundaries(ParticleContainer &container) {
        handler.handleBoundary(container);
    }
}//boundaries