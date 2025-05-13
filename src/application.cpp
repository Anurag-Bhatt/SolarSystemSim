#include <iostream>
#include <vector>
#include <cmath>
#include <SDL3/SDL.h>

#include "Vec2.hpp"
#include "CelestialBody.hpp"
#include "Window.hpp"
#include "SimulationConfig.hpp"

double simSpeed = 1.0;

int main(int argc, char* argv[]) {
    Window win("Solar System Simulation");

    // Masses in scaled units
    double sunMass = 1.989e30 * massScale;
    CelestialBody sun(30, 0, 0, sunMass, {255, 255, 0, 255});

    double earthMass = 5.972e24 * massScale;
    double earthDistance = 149.6e6 * distanceScale;
    double earthVelocity = std::sqrt(scaledG * sunMass / earthDistance) * 10 / distanceScale;
    CelestialBody earth(10, earthDistance, 0, earthMass, {0, 0, 255, 255});
    earth.SetVelocity(Vec2(0, earthVelocity));

    double venusMass = 4.87e24 * massScale;
    double venusDistance = 0.72 * earthDistance;
    double venusVelocity = std::sqrt(scaledG * sunMass / venusDistance) * 10 / distanceScale;
    CelestialBody venus(9.5, venusDistance, 0, venusMass, {200, 150, 100, 255});
    venus.SetVelocity(Vec2(0, venusVelocity));

    double marsMass = 6.42e23 * massScale;
    double marsDistance = 1.52 * earthDistance;
    double marsVelocity = std::sqrt(scaledG * sunMass / marsDistance) * 10 / distanceScale;
    CelestialBody mars(5.32, marsDistance, 0, marsMass, {255, 80, 80, 255});
    mars.SetVelocity(Vec2(0, marsVelocity));

    std::vector<CelestialBody*> bodies = {&sun, &earth, &venus, &mars};

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
        }

        // --- Rendering ---
        for (auto* body : bodies) {
            body->Draw(win);
        }

        win.presentRenderer();
    }

    return 0;
}
