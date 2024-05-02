//
// Created by kimj2 on 01.05.2024.
//

#pragma once

#include "../objects/ParticleContainer.h"
#include "Calculator.h"

namespace calculators {
    class DummyCalculator : public Calculator {
    private:

        void calculateX(ParticleContainer &particleContainer, double delta_t);

        void calculateF(ParticleContainer &particleContainer);


        void calculateV(ParticleContainer &particleContainer, double delta_t);

    public:

        DummyCalculator() = default;

        void calculate(ParticleContainer &particleContainer, double delta_t);

    };
}