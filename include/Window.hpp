#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_sdl3.h>
#include <IMGUI/imgui_impl_sdlrenderer3.h>
#include <IMGUI/imgui_stdlib.h>

#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include <random>

#include "Vec2.hpp"

class CelestialBody;

class Window {
public:
    Window(const char* windowTitle, int screenWidth = 1920, int screenHeight = 1080);
    ~Window();

    void clearRenderer();
    void presentRenderer();

    SDL_Renderer* getRenderer();
    SDL_Window* getWindow();

    void handleEvents();
    void updateDeltaTime(); 
    

    void addImGuiFrame();
    void renderImGui();    
    void showDemoWindowImGui();

    void showCelestialBodyData(std::vector<CelestialBody*> &CelestialBodies);

    bool shouldShowWindowImGui = false;
    
    bool isWindowRunning;
    bool isSimPaused;
    int screenWidth;
    int screenHeight;
    Vec2 screenCenter;

    double zoom = 1.0f;
    Vec2 panOffset = {0.0, 0.0};
    double panSpeed;

    double deltaTime = 0.0;
    double simSpeed = 1.0;
private:

    static void helpMaker(const char *description);


    ImGuiIO *m_ImGuiIO;    

    Uint64 now, last;

    SDL_Renderer* m_renderer;
    SDL_Window* m_window;
    SDL_Event m_event;
};

#endif // WINDOW_HPP
