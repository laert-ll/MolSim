//
// Created by Ujin on 27.05.2024.
//
#include <array>
#include <map>
#include "BoundaryEnums.h"

namespace boundaries {
    class BoundaryProperties{
    public:
//        BoundaryProperties() = default;
        // 2D Initializer
        BoundaryProperties(std::array<double, 2> domain, const std::map<BoundaryDirection, BoundaryType>& boundaryMap)
                : domain({domain[0], domain[1], 1}), boundaryMap(getBoundaryMapWithDefaults(boundaryMap)) {}

        const std::array<double, 3> &getDomain() const {
            return domain;
        }

        const std::map<BoundaryDirection, BoundaryType> &getBoundaryMap() const {
            return boundaryMap;
        }

    private:
        const std::array<double, 3> domain;

        const std::map<BoundaryDirection, BoundaryType> boundaryMap;

        static std::map<BoundaryDirection, BoundaryType> getBoundaryMapWithDefaults(const std::map<BoundaryDirection, BoundaryType>& originalMap) {
            std::map<BoundaryDirection, BoundaryType> mapWithDefaults = originalMap;

            // Setze Standardwerte für fehlende Einträge in boundaryMap
            for (const auto& direction : {BoundaryDirection::TOP,
                                          BoundaryDirection::BOTTOM,
                                          BoundaryDirection::LEFT,
                                          BoundaryDirection::RIGHT,
                                          BoundaryDirection::FRONT,
                                          BoundaryDirection::BACK}) {
                if (mapWithDefaults.find(direction) == mapWithDefaults.end()) {
                    mapWithDefaults[direction] = BoundaryType::OFF;
                }
            }
            return mapWithDefaults;
        }
    };
}