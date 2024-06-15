//
// Created by kimj2 on 05.06.2024.
//

#pragma once
class SimulationParameters {
public:
    SimulationParameters() : end_t(-1), delta_t(-1) {} // default constructor

    SimulationParameters(double end_t, double delta_t) : end_t(end_t), delta_t(delta_t) {}

    double getEnd_t() const {
        return end_t;
    }

    double getDelta_t() const {
        return delta_t;
    }

private:
    const double end_t;
    const double delta_t;
};