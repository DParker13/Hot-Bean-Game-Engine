#ifndef APPLICATION_H
#define APPLICATION_H

#include "EventSystem.h"
#include "GameObject.h"
#include <vector>
#include <memory>

class Application {
public:
    Application(const char* title, int width, int height);
    ~Application();

    void Run();

    void AddObject(std::shared_ptr<GameObject> object);

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* surface;
    bool quit;

    std::vector<std::shared_ptr<GameObject>> gameObjects;

    void InitSDL(const char* title, int width, int height);
    void CleanUpSDL();
};

#endif // APPLICATION_H
