//
// Created by kimj2 on 05.06.2024.
//

#pragma once
class SimulationParameters {
public:
    SimulationParameters() : end_t(-1), delta_t(-1) {} // default constructor

    SimulationParameters(double t_end, double delta_t) : end_t(t_end), delta_t(delta_t) {}

    [[nodiscard]] double getT_end() const {
        return end_t;
    }

    [[nodiscard]] double getDelta_t() const {
        return delta_t;
    }

private:
    const double end_t;
    const double delta_t;
};
