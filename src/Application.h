#include <vector>
#include <memory>
#include <iostream>
#include "EventSystem.h"
#include "GameObject.h"

class Application {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* surface;
    bool quit;

    std::vector<std::shared_ptr<GameObject>> gameObjects;

    void InitSDL(const char* title, int width, int height);
    void CleanUpSDL();
public:
    Application(const char* title, int width, int height);
    ~Application();

    void Run();

    void AddObject(std::shared_ptr<GameObject> gameObject);
};