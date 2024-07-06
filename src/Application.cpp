#include "Application.h"

Application::Application(const char* title, int width, int height) : window(nullptr), renderer(nullptr), quit(false) {
    InitSDL(title, width, height);
}

Application::~Application() {
    CleanUpSDL();
}

void Application::InitSDL(const char* title, int width, int height) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        exit(-1);
    }
    else {
        // Create window
        window = SDL_CreateWindow("Ocean Simulator", width, height, 0);
        if (window == nullptr) {
            std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            exit(-1);
        }
        else {
            // Create renderer for window
            renderer = SDL_CreateRenderer(window, NULL);
            if (renderer == nullptr) {
                std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
                SDL_DestroyWindow(window);
                SDL_Quit();
                exit(-1);
            }
            else {
                // Initialize renderer color
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                surface = SDL_GetWindowSurface(window);
                if (surface == nullptr) {
                    std::cerr << "Surface could not be created! SDL_Error: " << SDL_GetError() << std::endl;
                    SDL_DestroyWindow(window);
                    SDL_DestroyRenderer(renderer);
                    SDL_Quit();
                    exit(-1);
                }
            }
        }
    }
}

void Application::CleanUpSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroySurface(surface);
    SDL_Quit();
}

void Application::Run() {
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            else {
                //Notifies all GameObjects of event
                for (auto& object : gameObjects) {
                    object->OnEvent(event);
                }
            }
        }

        //Updates state of all GameObjects
        for (auto& object : gameObjects) {
            object->OnUpdate();
        }

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);

        //Renders all added GameObjects
        for (auto& object : gameObjects) {
            object->OnRender(surface, renderer);
        }

        SDL_RenderPresent(renderer);
    }
}

void Application::AddObject(std::shared_ptr<GameObject> gameObject) {
    gameObjects.push_back(gameObject);
}