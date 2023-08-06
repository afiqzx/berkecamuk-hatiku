#include "Application.hpp"
#include "Constants.h"
#include "Graphics.hpp"
#include "Particle.hpp"
#include "SDL2/SDL_events.h"
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

    m_particles.push_back(Particle(50.0, 100.0, 1.0));
    m_particles.push_back(Particle(100.0, 100.0, 0.1));
    m_particles.push_back(Particle(150.0, 100.0, 10.0));
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
            if (event.key.keysym.sym == SDLK_UP)
                pushForce.m_y = -20 * PIXELS_PER_METER;
            if (event.key.keysym.sym == SDLK_DOWN)
                pushForce.m_y = 20 * PIXELS_PER_METER;
            if (event.key.keysym.sym == SDLK_LEFT)
                pushForce.m_x = -20 * PIXELS_PER_METER;
            if (event.key.keysym.sym == SDLK_RIGHT)
                pushForce.m_x = 20 * PIXELS_PER_METER;
            break;
        case SDL_KEYUP:
            if (event.key.keysym.sym == SDLK_UP)
                pushForce.m_y = 0;
            if (event.key.keysym.sym == SDLK_DOWN)
                pushForce.m_y = 0;
            if (event.key.keysym.sym == SDLK_LEFT)
                pushForce.m_x = 0;
            if (event.key.keysym.sym == SDLK_RIGHT)
                pushForce.m_x = 0;
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

    for (Particle &particle : m_particles) {
        Vec2 wind = Vec2(0.0, 0.0) * PIXELS_PER_METER;
        Vec2 wind_resistance = Vec2(0.0, -0.9) * PIXELS_PER_METER;
        Vec2 gravity = Vec2(0.0, 9.8) * PIXELS_PER_METER;
        particle.AddForce(wind);
        particle.AddForce(wind_resistance);
        particle.AddForce((gravity * particle.m_mass));
        particle.AddForce(pushForce);

        particle.Integrate(deltaTime);

        if (particle.m_position.m_x - particle.m_radius <= 0) {
            particle.m_position.m_x = particle.m_radius;
            particle.m_velocity.m_x *= -1.0;
        } else if (particle.m_position.m_x + particle.m_radius >=
                   Graphics::Width()) {
            particle.m_position.m_x = Graphics::Width() - particle.m_radius;
            particle.m_velocity.m_x *= -1.0;
        } else if (particle.m_position.m_y - particle.m_radius <= 0) {
            particle.m_position.m_y = particle.m_radius;
            particle.m_velocity.m_y *= -1.0;
        } else if (particle.m_position.m_y + particle.m_radius >=
                   Graphics::Height()) {
            particle.m_position.m_y = Graphics::Height() - particle.m_radius;
            particle.m_velocity.m_y *= -1.0;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Render function (called several times per second to draw objects)
///////////////////////////////////////////////////////////////////////////////
void Application::Render() {
    Graphics::ClearScreen(0xFF056263);
    for (Particle &particle : m_particles) {
        Graphics::DrawFillCircle(particle.m_position.m_x,
                                 particle.m_position.m_y, 4, 0xFFFFFFFF);
    }
    Graphics::RenderFrame();
}

///////////////////////////////////////////////////////////////////////////////
// Destroy function to delete objects and close the window
///////////////////////////////////////////////////////////////////////////////
void Application::Destroy() { Graphics::CloseWindow(); }
