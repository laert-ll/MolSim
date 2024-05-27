//
// Created by houj on 5/23/24.
//

#include "BoundaryController.h"

namespace boundaries {
    BoundaryController::BoundaryController(const std::map<BoundaryDirection, BoundaryType>& boundaryMap,
                       std::unique_ptr<calculators::Calculator>& calculator,
                       std::array<double, 2> domain,
                       double sigma)
            : handler(BoundaryProperties(domain, boundaryMap), calculator, sigma) {};

    void BoundaryController::handleBoundaries(ParticleContainer &container) {
        handler.handleBoundary(container);
        }
}//boundaries