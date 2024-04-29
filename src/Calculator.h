#pragma once

#include "ParticleContainer.h"

class Calculator {

public:
    Calculator();

    /**
     * Calculate the new position for all particles using the Störmer-Verlet method
     */
    void calculateX(ParticleContainer &particleContainer, double delta_t);

    /**
     * Calculate the force between all pairs of unique particles
     */
    void calculateF(ParticleContainer &particleContainer);

    /**
     * Calculate the velocity for all particles using the Störmer-Verlet method
     */
    void calculateV(ParticleContainer &particleContainer, double delta_t);

    /**
     *  Plot the particles to a VTK-file
     */
    void plotParticles(int iteration, ParticleContainer &particleContainer);
};
