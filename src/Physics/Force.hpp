#pragma once

#include "Particle.hpp"
#include "Vec2.hpp"

struct Force {
    static Vec2 GenerateDragForce(const Particle &particle, float k);
    static Vec2 GenerateFrictionForce(const Particle &particle, float k);
};
