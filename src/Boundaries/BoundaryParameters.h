//
// Created by U-jin Hong on 25.05.24.
//
#include "BoundaryEnums.h"
#include <array>
namespace boundaries{
    class BoundaryParameters{
      BoundaryParameters(std::array<BoundaryType, 4> boundaryTypes, std::array<double, 4> boundaryPositions);


    };
}