
#include "Particle.hpp"
#include "Vec2.hpp"

Particle::Particle(float x, float y, float mass) {
    m_position = Vec2(x, y);
    m_mass = mass;
    m_inv_mass = 1 / mass;
    m_radius = 4.0;
}

void Particle::AddForce(const Vec2 &force) { m_sumForces += force; }

void Particle::Integrate(float dt) {
    Vec2 other_acceleration = m_sumForces * m_inv_mass;
    m_velocity += other_acceleration * dt;
    m_position += m_velocity * dt;

    ClearForces();
}

void Particle::ClearForces() {
    m_sumForces.m_x = 0.0;
    m_sumForces.m_y = 0.0;
}
