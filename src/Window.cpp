#include "Window.hpp"
#include "CelestialBody.hpp"
#include "SimulationConfig.hpp"

// Initialize global color constants
const SDL_Color Black = {0, 0, 0, 255};
const SDL_Color White = {255, 255, 255, 255};

SDL_Color ImVec4ToSDLColor(const ImVec4& color) {
    SDL_Color sdlColor;
    sdlColor.r = static_cast<Uint8>(color.x * 255.0f);
    sdlColor.g = static_cast<Uint8>(color.y * 255.0f);
    sdlColor.b = static_cast<Uint8>(color.z * 255.0f);
    sdlColor.a = static_cast<Uint8>(color.w * 255.0f);
    return sdlColor;
}


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

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    m_ImGuiIO = &ImGui::GetIO();
    m_ImGuiIO->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    m_ImGuiIO->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL3_InitForSDLRenderer(m_window, m_renderer);
    ImGui_ImplSDLRenderer3_Init(m_renderer);

    isWindowRunning = true;
    isSimPaused = false;

    now = SDL_GetPerformanceCounter();
}

Window::~Window()
{
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

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

SDL_Window *Window::getWindow()
{
    return m_window;
}

void Window::addImGuiFrame()
{
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
}

void Window::renderImGui()
{
    ImGui::Render();
    SDL_SetRenderScale(m_renderer, m_ImGuiIO->DisplayFramebufferScale.x, m_ImGuiIO->DisplayFramebufferScale.y);
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), m_renderer);
}

void Window::showDemoWindowImGui()
{
    if(shouldShowWindowImGui){
        ImGui::ShowDemoWindow(&shouldShowWindowImGui);
    }
}

void Window::showCelestialBodyData(std::vector<CelestialBody *> &CelestialBodies)
{
    if(shouldShowWindowImGui){
        // Show data
        ImGui::SetNextWindowSize(ImVec2(750.0f, 750.0f));
        ImGui::Begin("Celestial Bodies", &shouldShowWindowImGui);
        ImGui::Text("Application FPS: %0.1f", m_ImGuiIO->Framerate);
        
        Window::helpMaker(
            "Distance in AU.\n"
            "Mass in Kgs.\n"
            "Click the box to choose a color.\n"
        );
        ImGui::SeparatorText("Add new Planet");
        {
            static std::string newPlanetName;
            ImGui::InputText("Name ", &newPlanetName);
            // Data needed
            static double newRadius = 10.0f;
            ImGui::InputDouble("Radius of the Planet", &newRadius, 0.01f, 1.0f, "%0.4f");
            
            static double newDistanceFromSun = 2.0f;
            ImGui::InputDouble("Distance from sun", &newDistanceFromSun, 0.01f, 1.0f, "%0.4f");
            
            static double newMassInKg = 1.0f;
            ImGui::InputDouble("Mass in Kg", &newMassInKg, 0.05f, 1.0f, "%0.4f");
            
            static ImVec4 newPlanetColorVec4 = ImVec4(114.0f / 255.0f, 144.0f / 255.0f, 154.0f / 255.0f, 200.0f / 255.0f);
            static ImGuiColorEditFlags newPlanetColorBaseFlags = ImGuiColorEditFlags_None;
            ImGui::Text("Planets Color:");
            ImGui::SameLine();
            
            ImGui::ColorEdit3("Pick Me!!", (float*)&newPlanetColorVec4, newPlanetColorBaseFlags);
            
            static double addPlanetMessageTime = -1;
            if(ImGui::Button("Add Planet")){
            
                SDL_Color planetColorSDL = ImVec4ToSDLColor(newPlanetColorVec4);

                CelestialBodies.push_back(CelestialBodies.at(0)->CreatePlanet(newPlanetName, 
                                    newRadius, newDistanceFromSun, newMassInKg / massScale, planetColorSDL));

                
                addPlanetMessageTime = ImGui::GetTime();
            }

            if(addPlanetMessageTime > 0 && (ImGui::GetTime() - addPlanetMessageTime) < 2){
                ImGui::SameLine(); ImGui::Text("Added Planet");
            }

        }

        ImGui::SeparatorText("Delete Planet");
        {
        
        static std::vector<std::string> planetNamesStorage;
        planetNamesStorage.clear();

        std::vector<const char* > planetNames;
        if(!CelestialBodies.empty()){
            for(auto &cb : CelestialBodies){
                planetNamesStorage.push_back(cb->getName());
                planetNames.push_back(planetNamesStorage.back().c_str());
            }
        }

        static int selectPlanetIndex = -1;
        ImGui::Combo("Select Planet", &selectPlanetIndex, planetNames.data(), planetNames.size());
        
        double timeSinceDelete = -1;
        if(ImGui::Button("Delete Planet") && selectPlanetIndex > 0){

            timeSinceDelete = ImGui::GetTime();

            if(selectPlanetIndex > 0 && !CelestialBodies.empty() && selectPlanetIndex < CelestialBodies.size()){
                CelestialBodies.erase(CelestialBodies.begin() + selectPlanetIndex);
            }else {
                ImGui::BeginPopup("Index out of bounds");
                ImGui::EndPopup();
            }

            selectPlanetIndex = -1;
        }

        if(timeSinceDelete > 0 && (ImGui::GetTime() - timeSinceDelete) < 2){
           ImGui::SameLine(); ImGui::Text("Planet at index %d deleted", selectPlanetIndex);
        }

        }
        
        ImGui::SeparatorText("Simulation Setting");

        static double newSimSpeed = simSpeed;
        if(ImGui::InputDouble("Simulation Speed", &newSimSpeed, 0.1f, 1.0f, "%0.2f")){
            simSpeed = newSimSpeed;
        }
        if(ImGui::Button("Pause/Play")){
            isSimPaused = !isSimPaused;
        }

        ImGui::SeparatorText("Celestial Bodies Data");
        for(auto body : CelestialBodies){

            ImGui::Text("Name: %s ", body->getName().c_str());
            ImGui::Text("Mass: %f ", body->getMass());
            ImGui::Text("Radius: %f ", body->getRadius());
        }


        ImGui::End();
    }
}

void Window::handleEvents()
{
    panSpeed = 2000.0 * deltaTime;
        
    while(SDL_PollEvent(&m_event)) {
        
        ImGui_ImplSDL3_ProcessEvent(&m_event);

        if (ImGui::GetIO().WantCaptureKeyboard && (m_event.type == SDL_EVENT_KEY_DOWN || m_event.type == SDL_EVENT_MOUSE_WHEEL)) {
            continue;
        }

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

                    case SDL_SCANCODE_TAB:
                        shouldShowWindowImGui = !shouldShowWindowImGui;
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

void Window::helpMaker(const char *description)
{
    ImGui::TextDisabled("(?)");
    if (ImGui::BeginItemTooltip())
    {
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(description);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}