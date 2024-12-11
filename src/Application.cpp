#include "application.h"

/**
 * Constructs an Application object with the given title, width, and height.
 *
 * @param title The title of the window.
 * @param width The width of the window.
 * @param height The height of the window.
 *
 * @throws std::runtime_error If SDL initialization fails or window creation fails.
 */
Application::Application(std::string title, int width, int height) : window(nullptr), renderer(nullptr), quit(false) {
    InitSDL(title, width, height);
    deltaTime = 0.0f;
    previousFrameTime = 0.0f;
}

Application::~Application() {
    CleanUpSDL();
}

/**
 * Initializes SDL and creates a window for the application.
 *
 * @param title the title of the window
 * @param width the width of the window
 * @param height the height of the window
 *
 * @throws std::runtime_error if SDL initialization fails or window creation fails
 */
void Application::InitSDL(std::string title, int width, int height) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        exit(-1);
    }
    else {
        // Create window
        window = SDL_CreateWindow("Ocean Simulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                   width, height, SDL_WINDOW_RESIZABLE);
        if (window == nullptr) {
            std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            exit(-1);
        }
        else {
            // Create renderer for window
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == nullptr) {
                std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
                SDL_DestroyWindow(window);
                SDL_Quit();
                exit(-1);
            }
            else {
                // Initialize renderer color
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // Initialize TTF
                if (TTF_Init() < 0) {
                    std::cerr << "TTF could not be initialized! SDL_Error: " << SDL_GetError() << std::endl;
                    SDL_DestroyWindow(window);
                    SDL_DestroyRenderer(renderer);
                    SDL_Quit();
                    exit(-1);
                }
                else {
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
}

/**
 * Cleans up the SDL resources by destroying the renderer, window, surface,
 * and quitting the SDL library.
 *
 * @throws None
 */
void Application::CleanUpSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_FreeSurface(surface);
    TTF_Quit();
    SDL_Quit();
}

/**
 * Runs the main loop of the application, handling events, updating game objects, and rendering the scene.
 *
 * @return None
 *
 * @throws None
 */
void Application::Run(Core::CoreManager& coreManager) {
    SDL_Event event;

    while (!quit) {
        //Calculates delta time
        UpdateDeltaTime();

        //Polls for events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            else {
                coreManager.GetSystem<Systems::InputSystem>()->HandleEvent(coreManager, event, deltaTime);
                std::cout << event.type << std::endl;
            }
        }

       coreManager.GetSystem<Systems::PhysicsSystem>()->Update(coreManager, deltaTime);

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);

        coreManager.GetSystem<Systems::RenderSystem>()->Render(surface, renderer, coreManager);

        SDL_RenderPresent(renderer);
    }
}

/**
 * Updates the delta time by calculating the time difference between the current time and the previous frame time.
 * The calculated delta time is stored in a shared pointer and swapped with the existing delta time.
 *
 * @throws None
 */
void Application::UpdateDeltaTime() {
    Uint32 currentTime = SDL_GetTicks();
    float newDeltaTime = (currentTime - previousFrameTime) / 1000.0f;
    deltaTime = newDeltaTime;
    previousFrameTime = currentTime;
}