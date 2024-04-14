#include "Force.hpp"

Vec2 Force::GenerateDragForce(const Particle &particle, float k) {
    Vec2 dragForce = Vec2(0, 0);

    if (particle.m_velocity.MagnitudeSquared() > 0) {
        // Calculate the drag direction
        Vec2 dragDirection = particle.m_velocity.UnitVector() * -1.0;

        // Calculate drag magnitude
        float dragMagnitude = k * particle.m_velocity.MagnitudeSquared();

        // Generate the final drag force
        dragForce = dragDirection * dragMagnitude;
    }

    return dragForce;
}

Vec2 Force::GenerateFrictionForce(const Particle &particle, float k) {
    Vec2 frictionForce = Vec2(0.0, 0.0);

    // Calculate the friction direction
    Vec2 frictionDirection = particle.m_velocity.UnitVector() * -1.0;

    // Friction force (constant for now)
    float frictionMagnitude = k;

    // Calculate final friction force
    frictionForce = frictionDirection * frictionMagnitude;

    return frictionForce;
}

Vec2 Force::GenerateGravitationalForce(const Particle &particle_a,
                                       const Particle &particle_b, float G) {
    Vec2 d = (particle_b.m_position - particle_a.m_position);

    float distanceSquared = d.MagnitudeSquared();

    Vec2 attractionDirection = d.UnitVector();
    float attractionMagnitude =
        G * (particle_a.m_mass * particle_b.m_mass) / distanceSquared;

    Vec2 attractionForce = attractionDirection * attractionMagnitude;

    return attractionForce;
}
