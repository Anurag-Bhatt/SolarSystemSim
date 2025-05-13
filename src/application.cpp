#include <iostream>
#include <vector>
#include <cmath>
#include <SDL3/SDL.h>

#include "Vec2.hpp"
#include "CelestialBody.hpp"
#include "Window.hpp"
#include "SimulationConfig.hpp" 

/**
 * TODO: ADD IMGUI support for various "things" I can do.
 * // Could add loading and saving config files
 */

double simSpeed = 1.0;

int main(int argc, char* argv[]) {
    Window win("Solar System Simulation");

    // Masses in scaled units
    double sunMass = 1.989e30 * massScale;
    CelestialBody sun(30, 0, 0, sunMass, {255, 255, 0, 255});

    std::vector<CelestialBody*> bodies = {&sun};

    bodies.push_back(sun.CreatePlanet("Earth", 10, 1.0, 5.972e24, {0, 0, 255, 255}));
    bodies.push_back(sun.CreatePlanet("Mars", 5.3, 1.52, 6.42e23, {255, 100, 100, 255}));

    // --- Timing ---
    Uint64 now = SDL_GetPerformanceCounter();
    Uint64 last = 0;
    double deltaTime = 0.0;

    while (win.isWindowRunning) {
        // Delta Time
        last = now;
        now = SDL_GetPerformanceCounter();
        deltaTime = (double)((now - last) / (double)SDL_GetPerformanceFrequency()) * simSpeed;

        std::cout << "FPS: " << (deltaTime > 0 ? 1.0 / deltaTime : 0) << std::endl;

        win.handleEvents();
        win.clearRenderer();

        // --- Physics Update ---
        for (auto* body : bodies) {
            if (body != &sun) {
                body->ApplyGravity(sun, deltaTime);
            }
            body->Update(deltaTime);

            std::cout << *body << std::endl;

        }

        // --- Rendering ---
        for (auto* body : bodies) {
            body->Draw(win);
        }

        win.presentRenderer();
    }

    return 0;
}
