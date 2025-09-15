#pragma once

#include "Graphics.hpp"
#include "Physics/Particle.hpp"

class Application {
  private:
    bool running = false;
    int m_timePreviousFrame;
    std::vector<Particle> m_particles;

    Vec2 pushForce;

    SDL_Rect m_liquid;

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
