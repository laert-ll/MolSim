/*
 * Particle.cpp
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#include "Particle.h"
#include "spdlog/spdlog.h"
#include <iostream>
#include "../utils/ArrayUtils.h"

const double COMPARISON_TOLERANCE = 1e-6;

Particle::Particle(int type_arg) {
    type = type_arg;
    f = {0., 0., 0.};
    old_f = {0., 0., 0.};
    volume = 0;
    SPDLOG_TRACE("Particle generated!");
}

Particle::Particle(const Particle &other) {
    x = other.x;
    v = other.v;
    f = other.f;
    old_f = other.old_f;
    m = other.m;
    volume = other.volume;
    type = other.type;
    epsilon = other.epsilon;
    sigma = other.sigma;
    SPDLOG_TRACE("Particle generated by copy!");
}

Particle::Particle(std::array<double, 3> x_arg, std::array<double, 3> v_arg,
                   double m_arg, double volume_arg, int type_arg)
        : x(x_arg), v(v_arg), f({0., 0., 0.}), old_f({0., 0., 0.}),
          m(m_arg), volume(volume_arg), type(type_arg), sigma(1.0), epsilon(5.0) {
    SPDLOG_TRACE("Particle generated!");
}

Particle::Particle(std::array<double, 3> x_arg, std::array<double, 3> v_arg,
                   double m_arg, double volume_arg, int type_arg, double sig_arg, double eps_arg)
        : x(x_arg), v(v_arg), f({0., 0., 0.}), old_f({0., 0., 0.}),
          m(m_arg), volume(volume_arg), type(type_arg), sigma(sig_arg), epsilon(eps_arg) {
    SPDLOG_TRACE("Particle generated!");
}


Particle::~Particle() { SPDLOG_TRACE("Particle destructed!"); }

const std::array<double, 3> &Particle::getX() const { return x; }

const std::array<double, 3> &Particle::getV() const { return v; }

const std::array<double, 3> &Particle::getF() const { return f; }

const std::array<double, 3> &Particle::getOldF() const { return old_f; }

const double Particle::getM() const { return m; }

const double Particle::getVolume() const { return volume; }

const int Particle::getType() const { return type; }

void Particle::setX(const std::array<double, 3> &newX) {
    x = newX;
}

void Particle::setV(const std::array<double, 3> &newV) {
    v = newV;
}

void Particle::setF(const std::array<double, 3> &newF) {
    f = newF;
}

void Particle::setOldF(const std::array<double, 3> &newOldF) {
    old_f = newOldF;
}

void Particle::setM(const double newMass) {
    m = newMass;
}

void Particle::setVolume(const double newVolume) {
    volume = newVolume;
}

bool Particle::hasZeroVelocities() const {
    const auto &velocities = this->getV();
    return std::abs(velocities[0]) < COMPARISON_TOLERANCE && std::abs(velocities[1]) < COMPARISON_TOLERANCE &&
           std::abs(velocities[2]) < COMPARISON_TOLERANCE;
}


std::string Particle::toString() const {
    std::stringstream stream;
    stream << "Particle: X:" << x << " v: " << v << " f: " << f
           << " old_f: " << old_f << " m: " << m << " volume: "
           << volume << " type: " << type;
    return stream.str();
}

bool Particle::operator==(const Particle &other) const {
    return (x == other.x) and (v == other.v) and (f == other.f) and
           (type == other.type) and (m == other.m) and
           (volume == other.volume) and (old_f == other.old_f) and
           (sigma == other.sigma) and (epsilon == other.epsilon);
}

double Particle::getSigma() const {
    return sigma;
}

double Particle::getEpsilon() const {
    return epsilon;
}

std::ostream &operator<<(std::ostream &stream, Particle &p) {
    stream << p.toString();
    return stream;
}