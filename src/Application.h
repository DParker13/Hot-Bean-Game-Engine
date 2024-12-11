#include <SDL_ttf.h>
#include <vector>
#include <memory>
#include <iostream>

#include "core_manager.hpp"
#include "physics_system.hpp"
#include "render_system.hpp"
#include "input_system.hpp"

class Application {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* surface;
    bool quit;
    float deltaTime;
    float previousFrameTime;

    void InitSDL(std::string title, int width, int height);
    void CleanUpSDL();
public:
    Application(std::string title, int width, int height);
    ~Application();

    void Run(Core::CoreManager& coreManager);

    void UpdateDeltaTime();
};