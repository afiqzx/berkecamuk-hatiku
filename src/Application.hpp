#pragma once

#include "./Graphics.hpp"
#include "Particle.hpp"

class Application {
    private:
        bool running = false;
        Particle * m_particle;


    public:
        Application() = default;
        ~Application() = default;
        bool IsRunning();
        void Setup();
        void Input();
        void Update();
        void Render();
        void Destroy();
};

