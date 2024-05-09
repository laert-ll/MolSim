//
// Created by kimj2 on 08.05.2024.
//

#include <array>

/**
 * @struct ParticleParameters
 * @brief Parameters for a particle.
 */
struct ParticleParameters {
public:
    /**
     * @brief Constructor with initializer list.
     * @param x Initial position of the particle.
     * @param v Initial velocity of the particle.
     * @param m Initial mass of the particle.
     * @param volume Initial volume of the particle.
     * @param type Initial type of the particle.
     */
    ParticleParameters(std::array<double, 3> x, std::array<double, 3> v, double m, double volume, int type)
            : x(x), v(v), m(m), volume(volume), type(type) {}

    /**
     * @brief Get the position of the particle.
     * @return The position of the particle.
     */
    const std::array<double, 3>& getPosition() const {
        return x;
    }

    /**
     * @brief Get the velocity of the particle.
     * @return The velocity of the particle.
     */
    const std::array<double, 3>& getVelocity() const {
        return v;
    }


    /**
     * @brief Get the mass of the particle.
     * @return The mass of the particle.
     */
    double getMass() const {
        return m;
    }

    /**
     * @brief Get the Paraview volume of the particle.
     * @return The Paraview volume of the particle.
     */
    double getVolume() const {
        return volume;
    }

    /**
     * @brief Get the type of the particle.
     * @return The type of the particle.
     */
    int getType() const {
        return type;
    }

private:
    /**
     * @brief Position of the particle.
     */
    std::array<double, 3> x;

    /**
     * @brief Velocity of the particle.
     */
    std::array<double, 3> v;

    /**
     * @brief Mass of this particle.
     */
    double m;

    /**
     * @brief Paraview volume of this particle.
     */
    double volume;

    /**
     * @brief Type of the particle.
     * Use it for whatever you want (e.g. to separate
     * molecules belonging to different bodies, matters, and so on).
     */
    int type;
};