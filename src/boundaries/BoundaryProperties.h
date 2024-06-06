//
// Created by Ujin on 27.05.2024.
//
#pragma once
#include <array>
#include <map>
#include "BoundaryEnums.h"

namespace boundaries {
    /**
   * @class BoundaryProperties
   * @brief Holds the properties of the simulation boundaries.
   */
    class BoundaryProperties{
    public:
        /**
         * @brief Constructor for BoundaryProperties with 2D domain parameter.
         *
         * @param domain The domain size.
         * @param boundaryMap A map defining the boundary types for each direction.
         */
        BoundaryProperties(std::array<double, 2> domain, const std::map<BoundaryDirection, BoundaryType>& boundaryMap)
                : domain({domain[0], domain[1], 1}), boundaryMap(getBoundaryMapWithDefaults(boundaryMap)) {}

        /**
         * @brief Gets the domain size.
         *
         * @return The 3D domain size.
         */
        const std::array<double, 3> &getDomain() const {
            return domain;
        }

        /**
         * @brief Gets the boundary map.
         *
         * @return The boundary map.
         */
        const std::map<BoundaryDirection, BoundaryType> &getBoundaryMap() const {
            return boundaryMap;
        }

    private:
        const std::array<double, 3> domain;

        const std::map<BoundaryDirection, BoundaryType> boundaryMap;

        /**
         * @brief Generates a boundary map with default values.
         *
         * @param originalMap The original boundary map.
         * @return The boundary map with remaining directions filled with "Reflecting"
         * Since it's in 2D, the Front and Back
         */
        static std::map<BoundaryDirection, BoundaryType> getBoundaryMapWithDefaults(const std::map<BoundaryDirection, BoundaryType>& originalMap) {
            std::map<BoundaryDirection, BoundaryType> mapWithDefaults = originalMap;

            // Ensure FRONT and BACK are set to OFF if not already present
            if (mapWithDefaults.find(BoundaryDirection::FRONT) == mapWithDefaults.end()) {
                mapWithDefaults[BoundaryDirection::FRONT] = BoundaryType::OFF;
            }
            if (mapWithDefaults.find(BoundaryDirection::BACK) == mapWithDefaults.end()) {
                mapWithDefaults[BoundaryDirection::BACK] = BoundaryType::OFF;
            }

            // Set default for remaining directions to REFLECTING if not already present
            for (const auto &direction: {BoundaryDirection::TOP,
                                         BoundaryDirection::BOTTOM,
                                         BoundaryDirection::LEFT,
                                         BoundaryDirection::RIGHT}) {
                if (mapWithDefaults.find(direction) == mapWithDefaults.end()) {
                    mapWithDefaults[direction] = BoundaryType::REFLECTING;
                }
            }
            return mapWithDefaults;
        }
    };
}