//
// Created by kimj2 on 15.06.2024.
//

#pragma once

class ThermostatParameters {
public:
    ThermostatParameters() : start_temp(0.0), target_temp(0.0), applyFrequency(10), max_delta_temp(1.0),
                             dimension(3) {} // default constructor;

    ThermostatParameters(double start_temp, double target_temp, int applyFrequency, double max_delta_temp,
                         int dimension) :
            start_temp(start_temp), target_temp(target_temp), applyFrequency(applyFrequency),
            max_delta_temp(max_delta_temp), dimension(dimension) {}

    double getStartTemp() const {
        return start_temp;
    }

    double getTargetTemp() const {
        return target_temp;
    }

    int getApplyFrequency() const {
        return applyFrequency;
    }

    double getMaxDeltaTemp() const {
        return max_delta_temp;
    }

    int getDimension() const {
        return dimension;
    }

private:
    const double start_temp;
    const double target_temp;
    const int applyFrequency;
    const double max_delta_temp;
    const int dimension;
};