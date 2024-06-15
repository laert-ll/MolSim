//
// Created by kimj2 on 15.06.2024.
//
#pragma once

#include <map>
#include "boundaries/BoundaryEnums.h"

struct BoundaryParameters {
private:
    std::map<boundaries::BoundaryDirection, boundaries::BoundaryType> boundaryMap;

public:
    BoundaryParameters() = default;

    explicit BoundaryParameters(const std::map<boundaries::BoundaryDirection, boundaries::BoundaryType>& boundaryMap)
            : boundaryMap(boundaryMap) {}

    [[nodiscard]] const std::map<boundaries::BoundaryDirection, boundaries::BoundaryType>& getBoundaryMap() const {
        return boundaryMap;
    }
};