#pragma once

#include "../objects/LinkedCellContainer.h"
#include "Calculator.h"

namespace calculators {

    class LC_LJCalculator : public Calculator {

    public:

        LC_LJCalculator() = default;

        void calculateLC(LinkedCellContainer &linkedCellContainer, double delta_t) override;
        void calculateLC_X(LinkedCellContainer &linkedCellContainer, double delta_t);
        void calculateLC_V(LinkedCellContainer &linkedCellContainer, double delta_t);
        void calculateLC_F(LinkedCellContainer &linkedCellContainer);
        void calculateLC_FPairwise(Particle &particle1, Particle &particle2);
    };
}
