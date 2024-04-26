//
// Created by kimj2 on 26.04.2024.
//

#ifndef CALCULATORTEST_H
#define CALCULATORTEST_H

#include "../Particle.h"
#include "../Calculator.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <list>

class CalculatorTest {
private:
    std::list<Particle> particles;
    double timeStep;
    Calculator calculator;

public:
    explicit CalculatorTest(double delta_t) : particles(), timeStep(delta_t), calculator(Calculator()) {}

    void initializeParticlesForTest();
    void runSimulation(double endTime, double delta_t);
    bool checkPositions();
    void runTest();
};

#endif