#include "Application.hpp"
#include "Physics/Constants.h"
#include "Physics/Force.hpp"
#include "Graphics.hpp"
#include "Physics/Particle.hpp"
#include "SDL2/SDL_events.h"
#include "SDL_timer.h"

bool Application::IsRunning() { return running; }

///////////////////////////////////////////////////////////////////////////////
// Setup function (executed once in the beginning of the simulation)
///////////////////////////////////////////////////////////////////////////////
void Application::Setup() {
    running = Graphics::OpenWindow();

    m_timePreviousFrame = 0;

    Particle smallPlanet = Particle(550, 550, 1.0);
    smallPlanet.m_radius = 6;
    m_particles.push_back(smallPlanet);

    // Particle bigPlanet = Particle(500, 500, 20.0);
    // bigPlanet.m_radius = 20;
    // m_particles.push_back(bigPlanet);

    // m_liquid.x = 0;
    // m_liquid.y = Graphics::Height() / 2;
    // m_liquid.w = Graphics::Width();
    // m_liquid.h = Graphics::Height() / 2;
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
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                int x;
                int y;

                SDL_GetMouseState(&x, &y);
                m_particles.push_back(Particle(x, y, 5.0));
            }
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
        // Vec2 gravity = Vec2(0.0, 9.8) * PIXELS_PER_METER;
        // particle.AddForce((gravity * particle.m_mass));

        // Add force from arrow key input
        particle.AddForce(pushForce);

        // Apply drag force if we are inside the liquid
        // if (particle.m_position.m_y >= m_liquid.y) {
        //    Vec2 drag = Force::GenerateDragForce(particle, 0.001);
        //    particle.AddForce(drag);
        //}

        // Vec2 friction = Force::GenerateFrictionForce(particle, 10.0 *
        // PIXELS_PER_METER); particle.AddForce(friction);

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

    // loop everything except first particle (it is the anchor)
    for (int i = 1; i < m_particles.size(); i++) {
        Vec2 springForce = Force::GenerateSpringForce(
            m_particles[i], m_particles[0].m_position, 100, 10);
        m_particles[i].AddForce(springForce);
    }

    //// Applying a gravititional force to two particles
    // Vec2 gravityAttraction =
    // Force::GenerateGravitationalForce(m_particles[0], m_particles[1],
    // 1000.0, 5.0, 100); m_particles[0].AddForce(gravityAttraction);
    // m_particles[1].AddForce(-gravityAttraction);

    for (Particle &particle : m_particles) {
        particle.Integrate(deltaTime);
    }
}

///////////////////////////////////////////////////////////////////////////////
// Render function (called several times per second to draw objects)
///////////////////////////////////////////////////////////////////////////////
void Application::Render() {
    Graphics::ClearScreen(0xFF056263);

    // Graphics::DrawFillRect(m_liquid.x + m_liquid.w / 2,
    //                        m_liquid.y + m_liquid.h / 2, m_liquid.w,
    //                        m_liquid.h, 0xFF6E3713);

    for (Particle &particle : m_particles) {
        Graphics::DrawFillCircle(particle.m_position.m_x,
                                 particle.m_position.m_y, particle.m_radius,
                                 0xFFFFFFFF);
    }
    Graphics::RenderFrame();
}

///////////////////////////////////////////////////////////////////////////////
// Destroy function to delete objects and close the window
///////////////////////////////////////////////////////////////////////////////
void Application::Destroy() { Graphics::CloseWindow(); }
