//
// Created by kimj2 on 19.06.2024.
//
#pragma once
class LinkedCellsParameters {
public:
    LinkedCellsParameters() : linkedCellsUsed(false), cutOffRadius(1.0) {} // default constructor

    LinkedCellsParameters(bool linkedCellsUsed, double cutOffRadius) : linkedCellsUsed(linkedCellsUsed), cutOffRadius(cutOffRadius) {}

    [[nodiscard]] bool isLinkedCellsUsed() const {
        return linkedCellsUsed;
    }

    [[nodiscard]] double getCutOffRadius() const {
        return cutOffRadius;
    }

private:
    const bool linkedCellsUsed;
    const double cutOffRadius;
};