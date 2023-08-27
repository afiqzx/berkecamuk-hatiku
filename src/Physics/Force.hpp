#pragma once

#include "Vec2.hpp"
#include "Particle.hpp"

struct Force {
    static Vec2 GenerateDragForce(const Particle& particle, float k);
};

