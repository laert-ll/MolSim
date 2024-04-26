
#include "FileReader.h"
#include "Calculator.h"

#include <iostream>
#include <list>

constexpr double start_time = 0;
constexpr double default_end_time = 1000;
constexpr double default_delta_t = 0.014;

bool parseArguments(int argc, char *argv[], double &delta_t, double &end_time) {
    if (argc < 2 || argc > 4) {
        std::cerr << "Erroneous programme call! " << std::endl;
        std::cerr << "Usage: ./MolSym input_filename [delta_t] [end_time]" << std::endl;
        return false;
    }

    char* endptr;
    if (argc >= 3) {
        delta_t = std::strtod(argv[2], &endptr);
        if (*endptr != '\0' || delta_t <= 0.0) {
            std::cerr << "Invalid number for delta_t: " << argv[2] << std::endl;
            return false;
        }
    }
    if (argc == 4) {
        end_time = std::strtod(argv[3], &endptr);
        if (*endptr != '\0' || end_time <= 0.0) {
            std::cerr << "Invalid number for end_time: " << argv[3] << std::endl;
            return false;
        }
    }

    return true;
}

bool performSimulation(std::list<Particle> &particles, double &delta_t, double &end_time) {
    Calculator calculator;

    double current_time = start_time;
    int iteration = 0;

    while (current_time < end_time) {
        if (iteration > 1e6) {
            std::cerr << "Number of iterations exceeded 1 Mio." << std::endl;
            return false;
        }
        calculator.calculateX(particles, delta_t);
        calculator.calculateF(particles);
        calculator.calculateV(particles, delta_t);

        iteration++;
        if (iteration % 10 == 0) {
            calculator.plotParticles(iteration, particles);
        }
        std::cout << "Iteration " << iteration << " finished." << std::endl;

        current_time += delta_t;
    }

    std::cout << "output written. Terminating..." << std::endl;
    return true;
}

int main(int argc, char *argsv[]) {
    std::cout << "Hello from MolSim for PSE!" << std::endl;

    double delta_t = default_delta_t;
    double end_time = default_end_time;

    if (!parseArguments(argc, argsv, delta_t, end_time)) {
        return 1;
    }

    std::list<Particle> particles;

    FileReader fileReader;
    fileReader.readFile(particles, argsv[1]);

    std::cout << "Starting simulation with delta_t: " << delta_t << " and end_time: " << end_time << std::endl;
    bool success = performSimulation(particles, delta_t, end_time);
    if (!success) {
        std::cout << "Error occurred during the simulation." << std::endl;
        return 1;
    }
    std::cout << "Simulation completed successfully" << std::endl;
    return 0;
}
