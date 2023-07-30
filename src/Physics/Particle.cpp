
#include "Particle.hpp"

Particle::Particle(float x, float y, float mass) {
    m_position = Vec2(x, y);
    m_mass = mass;
    m_radius = 4.0;
}


