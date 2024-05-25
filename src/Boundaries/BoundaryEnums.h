//
// Created by houj on 5/23/24.
//
#pragma once

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
        LEFT
        };
}