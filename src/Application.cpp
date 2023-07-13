#include "Application.hpp"
#include <SDL_timer.h>

bool Application::IsRunning() {
    return running;
}

///////////////////////////////////////////////////////////////////////////////
// Setup function (executed once in the beginning of the simulation)
///////////////////////////////////////////////////////////////////////////////
void Application::Setup() {
    running = Graphics::OpenWindow();
    
    m_timePreviousFrame = 0;

    m_particle = new Particle(50.0, 100.0, 10.0);
    m_particle->m_velocity = Vec2(100.0, 30.0);
}

///////////////////////////////////////////////////////////////////////////////
// Input processing
///////////////////////////////////////////////////////////////////////////////
void Application::Input() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    running = false;
                break;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Update function (called several times per second to update objects)
///////////////////////////////////////////////////////////////////////////////
void Application::Update() {
    // Get the difference of time between each frame
    float deltaTime = (SDL_GetTicks() - m_timePreviousFrame) / 1000.0f;
    // SANITIZE! SANITIZE!
    if (deltaTime > 0.016) {
        deltaTime = 0.016;
    }

    m_timePreviousFrame = SDL_GetTicks();

    if (m_particle != nullptr) {
        m_particle->m_position += m_particle->m_velocity * deltaTime;
    }
}

///////////////////////////////////////////////////////////////////////////////
// Render function (called several times per second to draw objects)
///////////////////////////////////////////////////////////////////////////////
void Application::Render() {
    Graphics::ClearScreen(0xFF056263);
    Graphics::DrawFillCircle(m_particle->m_position.m_x, m_particle->m_position.m_y, 4, 0xFFFFFFFF);
    Graphics::RenderFrame();
}

///////////////////////////////////////////////////////////////////////////////
// Destroy function to delete objects and close the window
///////////////////////////////////////////////////////////////////////////////
void Application::Destroy() {
    if (m_particle != nullptr) {
        delete m_particle;
        m_particle = nullptr;
    }

    Graphics::CloseWindow();
}
