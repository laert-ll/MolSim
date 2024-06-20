//
// Created by houj on 5/23/24.
//

#include "BoundaryHandler.h"
#include "calculators/LC_LJCalculator.h"
#include <omp.h>

namespace boundaries {
    constexpr int boundaryWidthInNumCells = 2;


    void BoundaryHandler::preProcessBoundaries(ParticleContainer &container) const {
        for (auto it : properties.getBoundaryMap()) {
            if (it.second == BoundaryType::REFLECTING) {
                handleReflection(container, it.first);
            }
        }
    }

    void BoundaryHandler::preProcessBoundaries(LinkedCellContainer &linkedCellContainer) const {
        for (auto it : properties.getBoundaryMap()) {
            if (it.second == BoundaryType::REFLECTING) {
                handleReflection(linkedCellContainer, it.first);
            }
        }
    }

    void BoundaryHandler::postProcessBoundaries(ParticleContainer &container) const {
        for (auto it : properties.getBoundaryMap()) {
            if (it.second == BoundaryType::OUTFLOW)
                handleOutflow(container, it.first);
            else if (it.second == BoundaryType::PERIODIC)
                handlePeriodic(container, it.first);
        }
    }

    void BoundaryHandler::postProcessBoundaries(LinkedCellContainer &linkedCellContainer) const {
        for (auto it : properties.getBoundaryMap()) {
            if (it.second == BoundaryType::OUTFLOW)
                handleOutflow(linkedCellContainer, it.first);
            else if (it.second == BoundaryType::PERIODIC)
                handlePeriodic(linkedCellContainer, it.first);
        }
    }

    void BoundaryHandler::handleReflection(ParticleContainer &container, BoundaryDirection direction) const {
        const int relevantIndex = retrieveRelevantPositionIndex(direction);
        const bool isLowerBound = retrieveIsLowerBound(direction);

        double boundary = properties.getDomain()[relevantIndex];
        // If selected index is lower boundary (lowerX, lowerY, lowerZ)
        if (isLowerBound) {
            // for indexing x, y, z coordinate
//#pragma omp parallel for
            for (auto &p: container) {
                double distanceToBoundary = p.getX().at(relevantIndex);
                double tolerance = pow(2, 1 / 6) * p.getSigma();
                // only calculate reflection if near boundary
                if (distanceToBoundary < tolerance) {
                    Particle ghost{p};
                    if (relevantIndex == 0)
                        ghost.setX({-distanceToBoundary, p.getX().at(1), p.getX().at(2)});
                    else if (relevantIndex == 1)
                        ghost.setX({p.getX().at(0), -distanceToBoundary, p.getX().at(2)});
                    else
                        ghost.setX({p.getX().at(0), p.getX().at(1), -distanceToBoundary});
                    calculator->calculateFPairwise(p, ghost);
                }
            }
            return;
        }
//#pragma omp parallel for
        for (auto &p: container) {
            double distanceToBoundary = boundary - p.getX().at(relevantIndex);
            // only calculate reflection if near boundary
            double tolerance = pow(2, 1 / 6) * p.getSigma();
            if (distanceToBoundary < tolerance) {
                Particle ghost{p};
                if (relevantIndex == 0)
                    ghost.setX({boundary + distanceToBoundary, p.getX().at(1), p.getX().at(2)});
                else if (relevantIndex == 1)
                    ghost.setX({p.getX().at(0), boundary + distanceToBoundary, p.getX().at(2)});
                else
                    ghost.setX({p.getX().at(0), p.getX().at(1), boundary + distanceToBoundary});
                calculator->calculateFPairwise(p, ghost);
            }
        }
    }

    void
    BoundaryHandler::handleReflection(LinkedCellContainer &linkedCellContainer, BoundaryDirection direction) const {
        const int relevantIndex = retrieveRelevantPositionIndex(direction);
        const bool isLowerBound = retrieveIsLowerBound(direction);
        std::vector<std::shared_ptr<Cell>> boundaryCells = linkedCellContainer.getBoundaryCells(
                boundaryWidthInNumCells);

        double boundaryPosition = properties.getDomain()[relevantIndex];
        // If selected index is lower boundary (lowerX, lowerY, lowerZ)
        // for indexing x, y, z coordinate
        //#pragma omp parallel for
        for (const auto &cell: boundaryCells) {
            for (auto &p: cell->getParticles()) {
                double distanceToBoundary = isLowerBound ? p->getX().at(relevantIndex) : boundaryPosition -
                                                                                         p->getX().at(relevantIndex);
                double tolerance = pow(2, 1.0 / 6) * p->getSigma();
                // only calculate reflection if near boundary
                if (distanceToBoundary < tolerance) {
                    SPDLOG_DEBUG("Particle at position {} is near boundary", ArrayUtils::to_string(p->getX()));
                    Particle ghost{*p};
                    ghost.setV({0, 0, 0});
                    ghost.setF({0, 0, 0});
                    const double ghostPosition = isLowerBound ? -distanceToBoundary : boundaryPosition +
                                                                                      distanceToBoundary;
                    if (relevantIndex == 0)
                        ghost.setX({ghostPosition, p->getX().at(1), p->getX().at(2)});
                    else if (relevantIndex == 1)
                        ghost.setX({p->getX().at(0), ghostPosition, p->getX().at(2)});
                    else
                        ghost.setX({p->getX().at(0), p->getX().at(1), ghostPosition});
                    SPDLOG_DEBUG("Ghost particle created at position {}", ArrayUtils::to_string(ghost.getX()));
                    // Downcast from Calculator to LC_LJCalculator
                    auto lc_calculator = std::dynamic_pointer_cast<calculators::LC_LJCalculator>(calculator);
                    if (lc_calculator) {
                        // If the downcast is successful, call the method
                        lc_calculator->calculateFPairwise(*p, ghost);
                    } else {
                        // Handle the error case where the downcast fails
                        SPDLOG_ERROR("Failed to downcast from Calculator to LC_LJCalculator");
                    }
                }
            }
        }
    }

    void BoundaryHandler::handleOutflow(ParticleContainer &container, BoundaryDirection direction) const {
        const int relevantIndex = retrieveRelevantPositionIndex(direction);
        const bool isLowerBound = retrieveIsLowerBound(direction);

        for (auto &p: container) {
            auto &relevantParticlePositionValue = p.getX().at(relevantIndex);
            if ((isLowerBound && relevantParticlePositionValue <= 0) ||
                (!isLowerBound && relevantParticlePositionValue >= properties.getDomain()[relevantIndex])) {
                container.deleteParticle(p);
            }
        }
    }

    void BoundaryHandler::handleOutflow(LinkedCellContainer &linkedCellContainer, BoundaryDirection direction) const {
        const int relevantIndex = retrieveRelevantPositionIndex(direction);
        const bool isLowerBound = retrieveIsLowerBound(direction);
        std::vector<std::shared_ptr<Cell>> boundaryCells = linkedCellContainer.getBoundaryCells(
                boundaryWidthInNumCells);

        for (const auto &cell: boundaryCells) {
            for (auto &p: cell->getParticles()) {
                auto &relevantParticlePositionValue = p->getX().at(relevantIndex);
                if ((isLowerBound && relevantParticlePositionValue <= 0) ||
                    (!isLowerBound && relevantParticlePositionValue >= properties.getDomain()[relevantIndex])) {
                    linkedCellContainer.removeParticle(p);
                }
            }
        }
    }

    void BoundaryHandler::handlePeriodic(ParticleContainer &container, BoundaryDirection direction) const {
        const int relevantIndex = retrieveRelevantPositionIndex(direction);
        const bool isLowerBound = retrieveIsLowerBound(direction);

        double boundary = properties.getDomain()[relevantIndex];
        // If selected index is lower boundary (lowerX, lowerY, lowerZ)
        if (isLowerBound) {
//#pragma omp parallel for
            for (auto &p: container) {
                if (p.getX().at(relevantIndex) < 0) {
                    if (relevantIndex == 0)
                        p.setX({boundary + p.getX().at(0), p.getX().at(1), p.getX().at(2)});
                    if (relevantIndex == 1)
                        p.setX({p.getX().at(0), boundary + p.getX().at(1), p.getX().at(2)});
                    if (relevantIndex == 2)
                        p.setX({p.getX().at(0), p.getX().at(1), boundary + p.getX().at(2)});
                }
            }
            return;
        }
//#pragma omp parallel for
        for (auto &p: container) {
            if (p.getX().at(relevantIndex) >= boundary) {
                if (relevantIndex == 0)
                    p.setX({p.getX().at(0) - boundary, p.getX().at(1), p.getX().at(2)});
                if (relevantIndex == 1)
                    p.setX({p.getX().at(0), p.getX().at(1) - boundary, p.getX().at(2)});
                if (relevantIndex == 2)
                    p.setX({p.getX().at(0), p.getX().at(1), p.getX().at(2) - boundary});
            }
        }
    }

    void BoundaryHandler::handlePeriodic(LinkedCellContainer &linkedCellContainer, BoundaryDirection direction) const {
        const int relevantIndex = retrieveRelevantPositionIndex(direction);
        const bool isLowerBound = retrieveIsLowerBound(direction);
        std::vector<std::shared_ptr<Cell>> boundaryCells = linkedCellContainer.getBoundaryCells(
                boundaryWidthInNumCells);

        const double boundary = properties.getDomain()[relevantIndex];
        // If selected index is lower boundary (lowerX, lowerY, lowerZ)
        for (const auto &cell: boundaryCells) {
            for (auto &p: cell->getParticles()) {
                const double newParticlePosition = isLowerBound ? boundary + p->getX().at(relevantIndex) :
                                                   p->getX().at(relevantIndex) - boundary;
                if (p->getX().at(relevantIndex) < 0) {
                    if (relevantIndex == 0)
                        p->setX({newParticlePosition, p->getX().at(1), p->getX().at(2)});
                    if (relevantIndex == 1)
                        p->setX({p->getX().at(0), newParticlePosition, p->getX().at(2)});
                    if (relevantIndex == 2)
                        p->setX({p->getX().at(0), p->getX().at(1), newParticlePosition});
                }
            }
        }
    }

    bool BoundaryHandler::retrieveIsLowerBound(const BoundaryDirection &direction) const {
        switch (direction) {
            case BoundaryDirection::LEFT:
            case BoundaryDirection::BOTTOM:
            case BoundaryDirection::FRONT:
                return true;
            case BoundaryDirection::RIGHT:
            case BoundaryDirection::TOP:
            case BoundaryDirection::BACK:
                return false;
            default:
                throw std::invalid_argument("Invalid direction " + std::to_string(static_cast<int>(direction)));
        }
    }

    int BoundaryHandler::retrieveRelevantPositionIndex(const BoundaryDirection &direction) const {
        switch (direction) {
            case BoundaryDirection::LEFT:
            case BoundaryDirection::RIGHT:
                return 0;
            case BoundaryDirection::BOTTOM:
            case BoundaryDirection::TOP:
                return 1;
            case BoundaryDirection::FRONT:
            case BoundaryDirection::BACK:
                return 2;
            default:
                throw std::invalid_argument("Invalid direction " + std::to_string(static_cast<int>(direction)));
        }
    }
}