//
// Created by houj on 5/23/24.
//
#pragma once

#include <array>

namespace boundaries {
    enum class BoundaryType {
        REFLECTED,
        OUTFLOW,
        OFF
    };
    enum class BoundaryDirection {
        TOP,
        RIGHT,
        BOTTOM,
        LEFT,
        FRONT,
        BACK
        };

    // to iterate through all directions
    // Here - The order is: LowerX, Y, Z, HigherX, Y, Z
    const std::array<BoundaryDirection, 6> directions = {BoundaryDirection::BOTTOM,
                                                            BoundaryDirection::LEFT,
                                                            BoundaryDirection::FRONT,
                                                            BoundaryDirection::TOP,
                                                            BoundaryDirection::RIGHT,
                                                            BoundaryDirection::BACK};

}