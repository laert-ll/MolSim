//
// Created by kimj2 on 15.06.2024.
//

#pragma once

class ThermostatParameters {
public:
    ThermostatParameters() = default;

    ThermostatParameters(double start_temp, double target_temp, int applyFrequency, double max_delta_temp,
                         int dimension) :
            start_temp(start_temp), target_temp(target_temp), applyFrequency(applyFrequency),
            max_delta_temp(max_delta_temp), dimension(dimension) {}

    [[nodiscard]] double getStartTemp() const {
        return start_temp;
    }

    [[nodiscard]] double getTargetTemp() const {
        return target_temp;
    }

    [[nodiscard]] int getApplyFrequency() const {
        return applyFrequency;
    }

    [[nodiscard]] double getMaxDeltaTemp() const {
        return max_delta_temp;
    }

    [[nodiscard]] int getDimension() const {
        return dimension;
    }

private:
    double start_temp;
    double target_temp;
    int applyFrequency;
    double max_delta_temp;
    int dimension;
};