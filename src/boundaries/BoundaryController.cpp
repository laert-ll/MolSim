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
            : handler(BoundaryProperties(domain, boundaryMap), calculator, sigma) {
        SPDLOG_INFO("BoundaryController constructor called with the following parameters:");
        SPDLOG_INFO("Boundary map size: {}", boundaryMap.size());
        SPDLOG_INFO("Domain: [{}, {}]", domain[0], domain[1]);
        SPDLOG_INFO("Sigma: {}", sigma);
    };

    void BoundaryController::preProcessBoundaries(ParticleContainer &container) const {
        handler.preProcessBoundaries(container);
    }
    void BoundaryController::postProcessBoundaries(ParticleContainer &container) const {
        handler.postProcessBoundaries(container);
    }
}//boundaries