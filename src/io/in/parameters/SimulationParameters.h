//
// Created by kimj2 on 05.06.2024.
//

#pragma once
class SimulationParameters {
public:
    SimulationParameters() : end_t(-1), delta_t(-1), gravity(-1), dimension(2) {} // default constructor

    SimulationParameters(double end_t, double delta_t, double gravity, int dimension) : end_t(end_t), delta_t(delta_t), gravity(gravity), dimension(dimension) {}

    [[nodiscard]] double getEnd_t() const {
        return end_t;
    }

    [[nodiscard]] double getDelta_t() const {
        return delta_t;
    }

    [[nodiscard]] double getGravity() const {
        return gravity;
    }

    [[nodiscard]] int getDimension() const {
        return dimension;
    }

    void setEnd_t(double newEnd_t) {
        end_t = newEnd_t;
    }

    void setDelta_t(double newDelta_t) {
        delta_t = newDelta_t;
    }

    void setGravity(double newGravity) {
        gravity = newGravity;
    }

    void setDimension(int newDimension) {
        dimension = newDimension;
    }

private:
    double end_t;
    double delta_t;
    double gravity;
    int dimension;
};