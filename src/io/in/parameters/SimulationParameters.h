//
// Created by kimj2 on 05.06.2024.
//

#pragma once
class SimulationParameters {
public:
    SimulationParameters() : t_end(-1), delta_t(-1) {} // default constructor

    SimulationParameters(double t_end, double delta_t) : t_end(t_end), delta_t(delta_t) {}

    [[nodiscard]] double getT_end() const {
        return t_end;
    }

    [[nodiscard]] double getDelta_t() const {
        return delta_t;
    }

private:
    const double t_end;
    const double delta_t;
};
