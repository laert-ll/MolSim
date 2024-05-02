//
// Created by kimj2 on 01.05.2024.
//

#pragma once

#include "../objects/ParticleContainer.h"

namespace calculators {

    class Calculator {
    public:
        Calculator() = default;

        virtual ~Calculator() = default;

        virtual void calculate(ParticleContainer &particleContainer, double delta_t) {}

    private:
        virtual void calculateX(ParticleContainer &particleContainer, double delta_t) {}

        virtual void calculateF(ParticleContainer &particleContainer) {}

        virtual void calculateV(ParticleContainer &particleContainer, double delta_t) {}
    };
}