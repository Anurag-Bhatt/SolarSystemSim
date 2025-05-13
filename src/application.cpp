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

    std::vector<CelestialBody*> bodies = {&sun};

    bodies.push_back(sun.CreatePlanet("Earth", 10, 1.0, 5.972e24, {0, 0, 255, 255}));
    bodies.push_back(sun.CreatePlanet("Mars", 5.3, 1.52, 6.42e23, {255, 100, 100, 255}));
    bodies.push_back(sun.CreatePlanet("Venus", 9.50, 0.72, 4.87e24, {180, 120, 40, 255}));


    while (win.isWindowRunning) {
        // Delta Time
        win.updateDeltaTime();

        std::cout << "FPS: " << (win.deltaTime > 0 ? 1.0 / win.deltaTime : 0) << std::endl;

        win.handleEvents();
        win.clearRenderer();

        // --- Physics Update ---
        if(!win.isSimPaused){
            for (auto* body : bodies) {
                if (body != &sun) {
                    body->ApplyGravity(sun, win.deltaTime);
                }
                body->Update(win.deltaTime);

                // For debugging
                std::cout << *body << std::endl;
            }
        }

        // --- Rendering ---
        for (auto* body : bodies) {
            body->Draw(win);
        }

        win.presentRenderer();
    }

    return 0;
}
