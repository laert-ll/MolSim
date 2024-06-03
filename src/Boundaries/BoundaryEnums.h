//
// Created by houj on 5/23/24.
//
#pragma once

#include <array>

namespace boundaries {
    /**
     * @enum BoundaryType
     * @brief Defines the types of boundary conditions for the simulation.
     */
    enum class BoundaryType {
        REFLECTING, /**< Boundary reflects particles. */
        OUTFLOW,    /**< Boundary allows particles to flow out. */
        OFF         /**< Boundary is turned off. */
    };

    /**
     * @enum BoundaryDirection
     * @brief Defines the possible directions for boundaries in the simulation.
     */
    enum class BoundaryDirection {
        TOP,    /**< Upper boundary (Y-axis positive). */
        RIGHT,  /**< Right boundary (X-axis positive). */
        BOTTOM, /**< Lower boundary (Y-axis negative). */
        LEFT,   /**< Left boundary (X-axis negative). */
        FRONT,  /**< Front boundary (Z-axis positive). */
        BACK    /**< Back boundary (Z-axis negative). */
    };

    /**
     * @brief Array of all boundary directions for easy iteration.
     */
    const std::array<BoundaryDirection, 6> directions = {
            BoundaryDirection::LEFT,
            BoundaryDirection::BOTTOM,
            BoundaryDirection::FRONT,
            BoundaryDirection::RIGHT,
            BoundaryDirection::TOP,
            BoundaryDirection::BACK
    };
}