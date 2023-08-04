#include "Application.hpp"
#include "Constants.h"
#include "Graphics.hpp"
#include <SDL_timer.h>
#include <algorithm>
#include <ostream>

#include <iostream>

bool Application::IsRunning() { return running; }

///////////////////////////////////////////////////////////////////////////////
// Setup function (executed once in the beginning of the simulation)
///////////////////////////////////////////////////////////////////////////////
void Application::Setup() {
    running = Graphics::OpenWindow();

    m_timePreviousFrame = 0;

    m_particle = new Particle(50.0, 100.0, 10.0);
    m_particle->m_velocity = Vec2(50.0, 55.0);
    m_particle->m_acceleration = Vec2(0.0, 9.8 * PIXELS_PER_METER);
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
        Vec2 wind = Vec2(2.0, 2.0);
        m_particle->AddForce(wind);

        m_particle->Integrate(deltaTime);

        if (m_particle->m_position.m_x - m_particle->m_radius <= 0) {
            m_particle->m_position.m_x = m_particle->m_radius;
            m_particle->m_velocity.m_x *= -1.0;
        } else if (m_particle->m_position.m_x + m_particle->m_radius >=
                   Graphics::Width()) {
            m_particle->m_position.m_x =
                Graphics::Width() - m_particle->m_radius;
            m_particle->m_velocity.m_x *= -1.0;
        } else if (m_particle->m_position.m_y - m_particle->m_radius <= 0) {
            m_particle->m_position.m_y = m_particle->m_radius;
            m_particle->m_velocity.m_y *= -1.0;
        } else if (m_particle->m_position.m_y + m_particle->m_radius >=
                   Graphics::Height()) {
            m_particle->m_position.m_y =
                Graphics::Height() - m_particle->m_radius;
            m_particle->m_velocity.m_y *= -1.0;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Render function (called several times per second to draw objects)
///////////////////////////////////////////////////////////////////////////////
void Application::Render() {
    Graphics::ClearScreen(0xFF056263);
    Graphics::DrawFillCircle(m_particle->m_position.m_x,
                             m_particle->m_position.m_y, 4, 0xFFFFFFFF);
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
