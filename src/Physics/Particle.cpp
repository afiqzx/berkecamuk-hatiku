
#include "Particle.hpp"
#include "Vec2.hpp"

Particle::Particle(float x, float y, float mass) {
    m_position = Vec2(x, y);
    m_mass = mass;
    m_radius = 4.0;
}

void Particle::Integrate(float dt) {
    Vec2 other_acceleration = m_sumForces / m_mass;
    m_velocity += (m_acceleration + other_acceleration) * dt;
    m_position += m_velocity * dt;
}

void Particle::AddForce(const Vec2 &force) { m_sumForces += force; }

void Particle::ClearForces() {
    m_sumForces.m_x = 0.0;
    m_sumForces.m_y = 0.0;
}
