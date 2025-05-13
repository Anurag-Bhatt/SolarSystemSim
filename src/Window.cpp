#include "Window.hpp"


// Initialize global color constants
const SDL_Color Black = {0, 0, 0, 255};
const SDL_Color White = {255, 255, 255, 255};

Window::Window(const char *windowTitle, int screenWidth, int screenHeight) :
    isWindowRunning(true),
    screenWidth(screenWidth),
    screenHeight(screenHeight),
    screenCenter(screenWidth/2.0, screenHeight/2.0)
{
    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return;
        isWindowRunning = false;
    }

    // Create window
    m_window = SDL_CreateWindow(windowTitle, screenWidth, screenHeight, 0);
    if(!m_window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
        isWindowRunning = false;
    }

    // Create renderer
    m_renderer = SDL_CreateRenderer(m_window, nullptr);
    if(!m_renderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return;
        isWindowRunning = false;
    }

    isWindowRunning = true;
    isSimPaused = false;

    now = SDL_GetPerformanceCounter();
}



Window::~Window()
{
    if(m_renderer) SDL_DestroyRenderer(m_renderer);
    if(m_window) SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Window::clearRenderer()
{
    SDL_SetRenderDrawColor(m_renderer, Black.r, Black.g, Black.b, Black.a);
    SDL_RenderClear(m_renderer);
}

void Window::presentRenderer()
{
    SDL_RenderPresent(m_renderer);
}

SDL_Renderer *Window::getRenderer()
{
    return m_renderer;
}

void Window::handleEvents()
{
    const double panSpeed = 2000.0 * deltaTime;

    while(SDL_PollEvent(&m_event)) {
        switch(m_event.type) {
            case SDL_EVENT_QUIT:
                isWindowRunning = false;
            break;
            
            case SDL_EVENT_KEY_DOWN:
                switch (m_event.key.scancode){
                case SDL_SCANCODE_ESCAPE:
                    isWindowRunning = false;
                break;
                
                case SDL_SCANCODE_W:
                    panOffset.y -= panSpeed/zoom;
                break;
                case SDL_SCANCODE_S:
                    panOffset.y += panSpeed/zoom;
                break;
                case SDL_SCANCODE_A:
                    panOffset.x -= panSpeed/zoom;
                break;
                case SDL_SCANCODE_D:
                    panOffset.x += panSpeed/zoom;
                break;
                case SDL_SCANCODE_P:
                    isSimPaused = !isSimPaused;
                break;
                case SDL_SCANCODE_RIGHT:
                    simSpeed *= 2;
                break;
                case SDL_SCANCODE_LEFT:
                    simSpeed /= 2;
                break;
            }

            break;
            // Add other event handlers

            case SDL_EVENT_MOUSE_WHEEL:
                if(m_event.wheel.y != 0){
                    zoom += m_event.wheel.y * 0.01f;
                }
            break;
        }
    }
}

void Window::updateDeltaTime()
{
    last = now;
    now = SDL_GetPerformanceCounter();
    deltaTime = (double)((now - last) / (double)SDL_GetPerformanceFrequency()) * simSpeed;

}
