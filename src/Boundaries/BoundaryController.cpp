//
// Created by houj on 5/23/24.
//

#include "BoundaryController.h"
#include "spdlog/spdlog.h"

namespace boundaries {
    BoundaryController::BoundaryController(const std::map<BoundaryDirection, BoundaryType>& boundaryMap,
                                           calculators::Calculator *calculator,
                                           std::array<double, 2> domain,
                                           double sigma)
            : handler(BoundaryProperties(domain, boundaryMap), std::move(calculator), sigma) {
        spdlog::info("BoundaryController constructor called with the following parameters:");
        spdlog::info("Boundary map size: {}", boundaryMap.size());
        spdlog::info("Domain: [{}, {}]", domain[0], domain[1]);
        spdlog::info("Sigma: {}", sigma);
    };

    void BoundaryController::handleBoundaries(ParticleContainer &container) const {
        handler.handleBoundary(container);
        }
}//boundaries