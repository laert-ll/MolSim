/*
 * Particle.h
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#pragma once

#include <array>
#include <string>

class Particle {

private:
    /**
     * Position of the particle
     */
    std::array<double, 3> x;

    /**
     * Velocity of the particle
     */
    std::array<double, 3> v;

    /**
     * Force effective on this particle
     */
    std::array<double, 3> f;

    /**
     * Force which was effective on this particle
     */
    std::array<double, 3> old_f;

    /**
     * Mass of this particle
     */
    double m;

    /**
     * Paraview volume of this particle
     */
    double volume;

    /**
     * Type of the particle. Use it for whatever you want (e.g. to separate
     * molecules belonging to different bodies, matters, and so on)
     */
    int type;

public:
    explicit Particle(int type = 0);

    Particle(const Particle &other);

    Particle(
            // for visualization, we need always 3 coordinates
            // -> in case of 2d, we use only the first and the second
            std::array<double, 3> x_arg, std::array<double, 3> v_arg, 
            double m_arg, double volume_arg, int type = 0);

    virtual ~Particle();

    const std::array<double, 3> &getX() const;

    const std::array<double, 3> &getV() const;

    const std::array<double, 3> &getF() const;

    const std::array<double, 3> &getOldF() const;

    const double getM() const;

    const double getVolume() const;

    const int getType() const;

    void setX(const std::array<double, 3> &newX);

    void setV(const std::array<double, 3> &newV);

    void setF(const std::array<double, 3> &newF);

    void setOldF(const std::array<double, 3> &newOldF);

    void setVolume(const double volume);

    bool operator==(Particle &other);

    std::string toString() const;
};

std::ostream &operator<<(std::ostream &stream, Particle &p);
