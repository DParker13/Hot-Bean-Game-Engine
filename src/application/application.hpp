#include <SDL_ttf.h>
#include <vector>
#include <memory>
#include <iostream>

#include "../managers/core_manager.hpp"
#include "../gameobjects/text.hpp"
#include "../gameobjects/player.hpp"

#include "../systems/physics_system.hpp"
#include "../systems/render_system.hpp"
#include "../systems/input_system.hpp"
#include "../systems/player_controller_system.hpp"
#include "../systems/ui_system.hpp"

class Application {
private:
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    SDL_Surface* _surface;
    Core::CoreManager _coreManager;
    bool _quit;
    float _deltaTime;
    float _previousFrameTime;

    void InitSDL(std::string title, int width, int height);
    void CleanUpSDL();
public:
    Application(std::string title, int width, int height);
    ~Application();

    void InitCore();
    void Run();

    void UpdateDeltaTime();
};