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
        PERIODIC,
        OFF         /**< Boundary is turned off. */
    };

    /**
     * @enum BoundaryDirection
     * @brief Defines the possible directions for boundaries in the simulation.
     */
    enum class BoundaryDirection {
        TOP,    /**< Upper boundary (Y-axis High). */
        RIGHT,  /**< Right boundary (X-axis High). */
        BOTTOM, /**< Lower boundary (Y-axis Low). */
        LEFT,   /**< Left boundary (X-axis Low). */
        FRONT,  /**< Front boundary (Z-axis High). */
        BACK    /**< Back boundary (Z-axis Low). */
    };
}