//
// Created by kimj2 on 15.06.2024.
//
#pragma once

#include <map>
#include "boundaries/BoundaryEnums.h"

struct BoundaryParameters {
private:
    std::map<boundaries::BoundaryDirection, boundaries::BoundaryType> boundaryMap;
    std::array<double, 3> domain;

public:
    BoundaryParameters() = default;

    BoundaryParameters(const std::map<boundaries::BoundaryDirection, boundaries::BoundaryType>& boundaryMap, const std::array<double, 3>& domain)
            : boundaryMap(boundaryMap), domain(domain) {}

    [[nodiscard]] const std::map<boundaries::BoundaryDirection, boundaries::BoundaryType>& getBoundaryMap() const {
        return boundaryMap;
    }

    [[nodiscard]] const std::array<double, 3>& getDomain() const {
        return domain;
    }
};