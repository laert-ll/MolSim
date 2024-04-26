//
// Created by kimj2 on 24.04.2024.
//
#ifndef CALCULATOR_H
#define CALCULATOR_H
#pragma once

#include "Particle.h"
#include "list"

class Calculator {

public:
    Calculator();

    /**
     * calculate the force for all particles
     */
    void calculateF(std::list<Particle> &particles);

    /**
     * calculate the position for all particles
     */
    void calculateX(std::list<Particle> &particles, double delta_t);

    /**
     * calculate the position for all particles
     */
    void calculateV(std::list<Particle> &particles, double delta_t);

    /**
     *  plot particles to a xyz-file
     */
    void plotParticles(int iteration, std::list<Particle> &particles);
};

#endif