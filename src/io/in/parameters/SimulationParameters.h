//
// Created by kimj2 on 05.06.2024.
//

#pragma once
class SimulationParameters {
public:
    SimulationParameters() : end_t(-1), delta_t(-1) {} // default constructor

    SimulationParameters(double end_t, double delta_t) : end_t(end_t), delta_t(delta_t) {}

    [[nodiscard]] double getEnd_t() const {
        return end_t;
    }

    [[nodiscard]] double getDelta_t() const {
        return delta_t;
    }

    void setEnd_t(double newEnd_t) {
        end_t = newEnd_t;
    }

    void setDelta_t(double newDelta_t) {
        delta_t = newDelta_t;
    }

private:
    double end_t;
    double delta_t;
};