//
// Created by houj on 5/23/24.
//

#include "BoundaryHandler.h"
#include <omp.h>

namespace boundaries {

    void BoundaryHandler::preProcessBoundaries(ParticleContainer &container) const {
        for (auto it = properties.getBoundaryMap().begin(); it != properties.getBoundaryMap().end(); ++it) {
            if (it->second == BoundaryType::REFLECTING) {
                handleReflection(container, it->first);
            }
        }
    }

        void BoundaryHandler::postProcessBoundaries(ParticleContainer &container) const {
            for (auto it = properties.getBoundaryMap().begin(); it != properties.getBoundaryMap().end(); ++it) {
                if (it->second == BoundaryType::OUTFLOW)
                    handleOutflow(container, it->first);
            }
    }
    void BoundaryHandler::handleReflection(ParticleContainer &container, BoundaryDirection direction) const {
        // If selected index is lower boundary (lowerX, lowerY, lowerZ)
        if (direction == BoundaryDirection::BOTTOM || direction == BoundaryDirection::LEFT ||
            direction == BoundaryDirection::FRONT) {
            double tolerance = pow(2, 1/6) * sigma;
            // for indexing x, y, z coordinate
            int index;
            if (direction == BoundaryDirection::LEFT)
                index = 0;
            else if (direction == BoundaryDirection::BOTTOM)
                index = 1;
            else
                index = 2;
#pragma omp parallel for
            for (auto &p: container) {
                double distanceToBoundary = p.getX().at(index);
                // only calculate reflection if near boundary
                if (distanceToBoundary < tolerance) {
                    Particle ghost{p};
                    if (index == 0)
                        ghost.setX({-distanceToBoundary, p.getX().at(1), p.getX().at(2)});
                    else if (index == 1)
                        ghost.setX({p.getX().at(0), -distanceToBoundary, p.getX().at(2)});
                    else
                        ghost.setX({p.getX().at(0), p.getX().at(1), -distanceToBoundary});
                    calculator->calculateFPairwise(p, ghost);
                }
            }
            return;
        }
        int index;
        if (direction == BoundaryDirection::RIGHT)
            index = 0;
        else if (direction == BoundaryDirection::TOP)
            index = 1;
        else
            index = 2;
        double boundary = properties.getDomain()[index];
        double tolerance = pow(2, 1/6) * sigma;
#pragma omp parallel for
        for (auto &p: container) {
            double distanceToBoundary = p.getX().at(index) - boundary;
            // only calculate reflection if near boundary
            if (distanceToBoundary < tolerance) {
                Particle ghost{p};
                if (index == 0)
                    ghost.setX({boundary - distanceToBoundary, p.getX().at(1), p.getX().at(2)});
                else if (index == 1)
                    ghost.setX({p.getX().at(0), boundary - distanceToBoundary, p.getX().at(2)});
                else
                    ghost.setX({p.getX().at(0), p.getX().at(1), boundary - distanceToBoundary});
                calculator->calculateFPairwise(p, ghost);
            }
        }
    }

    void BoundaryHandler::handleOutflow(ParticleContainer &container, BoundaryDirection direction) const {
        int index;
        bool checkLowerBound = false;
        switch (direction) {
            case BoundaryDirection::LEFT:
                index = 0;
                checkLowerBound = true;
                break;
            case BoundaryDirection::RIGHT:
                index = 0;
                break;
            case BoundaryDirection::BOTTOM:
                index = 1;
                checkLowerBound = true;
                break;
            case BoundaryDirection::TOP:
                index = 1;
                break;
            case BoundaryDirection::FRONT:
                index = 2;
                checkLowerBound = true;
                break;
            case BoundaryDirection::BACK:
                index = 2;
                break;
        }
        for (auto &p: container) {
            auto &el = p.getX().at(index);
            if ((checkLowerBound && el <= 0) || (!checkLowerBound && el >= properties.getDomain()[index])) {
                container.deleteParticle(p);
            }
        }
    }

    BoundaryHandler::BoundaryHandler(BoundaryProperties properties, calculators::Calculator *calculator,
                                     double sigma)
            : properties(std::move(properties)), sigma(sigma), calculator(calculator) {}
}