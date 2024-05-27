//
// Created by houj on 5/23/24.
//

#include "BoundaryHandler2D.h"

namespace boundaries {

    void BoundaryHandler2D::handleBoundary(ParticleContainer &container) const{

        for (int i = 0; i < 6; i++) {
            BoundaryType type = properties.getBoundaryMap().at(directions[i]);
            if (type == BoundaryType::REFLECTED)
                handleReflection(container, directions[i]);
            if (type == BoundaryType::OUTFLOW)
                handleOutflow(container, directions[i]);
        }
    }

    void BoundaryHandler2D::handleReflection(ParticleContainer &container, BoundaryDirection direction) const{
        // If selected index is lower boundary (lowerX, lowerY, lowerZ)
        if (direction == BoundaryDirection::BOTTOM || direction == BoundaryDirection::LEFT || direction == BoundaryDirection::FRONT) {
            double tolerance = 1.12246204831 * sigma;
            // for indexing x, y, z coordinate
            int index;
            if (direction == BoundaryDirection::BOTTOM)
                index = 0;
            else if (direction == BoundaryDirection::LEFT)
                index = 1;
            else
                index = 2;
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
                    calculator->calculateFpair(p, ghost);
                }
            }
            return;
        }
        int index;
        if (direction == BoundaryDirection::TOP)
            index = 0;
        else if (direction == BoundaryDirection::RIGHT)
            index = 1;
        else
            index = 2;
        double boundary = properties.getDomain()[index];
        double tolerance = 1.12246204831 * sigma;
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
                    calculator->calculateFpair(p, ghost);
                }
            }
        }

    void BoundaryHandler2D::handleOutflow(ParticleContainer &container, BoundaryDirection direction) const{
        // Outflow Handling
        return;
    }

    BoundaryHandler2D::BoundaryHandler2D(BoundaryProperties properties, std::unique_ptr<calculators::Calculator>& calculator, double sigma)
    : properties(std::move(properties)), calculator(std::move(calculator)), sigma(sigma) {
    }

//    const BoundaryProperties &BoundaryHandler2D::getProperties() const {
//        return properties;
//    }

//    const double BoundaryHandler2D::getSigma() const {
//        return sigma;
//    }
//
//    const std::unique_ptr<calculators::Calculator> &BoundaryHandler2D::getCalculator() const {
//        return calculator;
//    }


}