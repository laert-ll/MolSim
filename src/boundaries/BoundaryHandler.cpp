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
            if (it->second == BoundaryType::PERIODIC)
                handlePeriodic(container, it->first);
        }
    }
    void BoundaryHandler::handleReflection(ParticleContainer &container, BoundaryDirection direction) const {
        bool checkLowerBound = false;
        int index = 0;
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
        double boundary = properties.getDomain()[index];
        // If selected index is lower boundary (lowerX, lowerY, lowerZ)
        if (checkLowerBound) {
            // for indexing x, y, z coordinate
#pragma omp parallel for
            for (auto &p: container) {
                double distanceToBoundary = p.getX().at(index);
                double tolerance = pow(2, 1/6) * p.getSigma();
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
#pragma omp parallel for
        for (auto &p: container) {
            double distanceToBoundary = boundary -p.getX().at(index);
            // only calculate reflection if near boundary
            double tolerance = pow(2, 1/6) * p.getSigma();
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

    void BoundaryHandler::handlePeriodic(ParticleContainer &container, BoundaryDirection direction) const {
        bool checkLowerBound = false;
        int index = 0;
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
        double boundary = properties.getDomain()[index];
        // If selected index is lower boundary (lowerX, lowerY, lowerZ)
        if (checkLowerBound) {
#pragma omp parallel for
            for (auto &p: container) {
                if (p.getX().at(index) < 0) {
                    if(index == 0)
                        p.setX({boundary + p.getX().at(0), p.getX().at(1), p.getX().at(2)});
                    if(index == 1)
                        p.setX({p.getX().at(0), boundary + p.getX().at(1), p.getX().at(2)});
                    if(index == 2)
                        p.setX({p.getX().at(0), p.getX().at(1), boundary + p.getX().at(2)});
                }
            }
            return;
        }
#pragma omp parallel for
        for (auto &p: container) {
            if (p.getX().at(index) >= boundary) {
                if(index == 0)
                    p.setX({p.getX().at(0) - boundary, p.getX().at(1), p.getX().at(2)});
                if(index == 1)
                    p.setX({p.getX().at(0), p.getX().at(1) - boundary, p.getX().at(2)});
                if(index == 2)
                    p.setX({p.getX().at(0), p.getX().at(1), p.getX().at(2) - boundary});
            }
        }
    }
}