//
// Created by kimj2 on 01.05.2024.
//
#include "DummyCalculator.h"

namespace calculators {

    void DummyCalculator::calculate(ParticleContainer &particleContainer, double delta_t) {
        calculateF(particleContainer);
        calculateX(particleContainer, delta_t);
        calculateV(particleContainer, delta_t);
    }

    void DummyCalculator::calculateF(ParticleContainer &particleContainer) {}

    void DummyCalculator::calculateX(ParticleContainer &particleContainer, double delta_t) {}

    void DummyCalculator::calculateV(ParticleContainer &particleContainer, double delta_t) {}
}
