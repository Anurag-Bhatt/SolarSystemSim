#include <SDL3/SDL.h>

#include <iostream>
#include <vector>
#include <cmath>

#include "Vec2.hpp"
#include "CelestialBody.hpp"
#include "Window.hpp"
#include "SimulationConfig.hpp" 

int main(int argc, char* argv[]) {
    Window win("Solar System Simulation");

    // Mass in scaled units
    CelestialBody sun("Sun", 30, 0, 0, 1.989e30 * massScale, {255, 255, 0, 255});

    std::vector<CelestialBody*> bodies = {&sun};

    bodies.push_back(sun.CreatePlanet("Earth", 10, 1.0, 5.972e24, {0, 0, 255, 255}));
    bodies.push_back(sun.CreatePlanet("Mars", 5.3, 1.52, 6.42e23, {255, 100, 100, 255}));
    bodies.push_back(sun.CreatePlanet("Venus", 9.50, 0.72, 4.87e24, {180, 120, 40, 255}));

    while (win.isWindowRunning) {
        // Delta Time
        win.updateDeltaTime();

        std::cout << "FPS: " << (win.deltaTime > 0 ? 1.0 / win.deltaTime : 0) << std::endl;

        // prepares for updating and rendering
        win.handleEvents();
        win.clearRenderer();

        // Imgui rendering
        win.addImGuiFrame();
        // win.showDemoWindowImGui();
        win.showCelestialBodyData(bodies);

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

        // win.draw(bodies); instead of the below code
        // --- Rendering ---
        for (auto* body : bodies) {
            body->Draw(win);
        }

        win.renderImGui();
        win.presentRenderer();
    }

    return 0;
}
