#pragma once

#include "Vec2.hpp"

struct Particle {
    Vec2 m_position;
    Vec2 m_velocity;
    Vec2 m_acceleration;
    Vec2 m_sumForces;

    float m_mass;
    float m_radius;

    Particle(float x, float y, float mass);
    ~Particle() = default;

    void Integrate(float delta_time);

    void AddForce(const Vec2 &force);
    void ClearForces();
};
