#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL3/SDL.h>
#include <iostream>
#include "Vec2.hpp"

class Window {
public:
    Window(const char* windowTitle, int screenWidth = 1920, int screenHeight = 1080);
    ~Window();

    void clearRenderer();
    void presentRenderer();
    SDL_Renderer* getRenderer();
    void handleEvents();
    void updateDeltaTime(); 

    bool isWindowRunning;
    int screenWidth;
    int screenHeight;
    Vec2 screenCenter;

    double zoom = 1.0f;
    Vec2 panOffset = {0.0, 0.0};

    double deltaTime = 0.0;
    double simSpeed = 1.0l;
private:

    Uint64 now, last;

    SDL_Renderer* m_renderer;
    SDL_Window* m_window;
    SDL_Event m_event;
};

#endif // WINDOW_HPP
