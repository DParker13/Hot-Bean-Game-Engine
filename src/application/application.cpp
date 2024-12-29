#include "application.hpp"

namespace Application {
    /**
     * Constructs an Application object with the given title, width, and height.
     *
     * @param title The title of the window.
     * @param width The width of the window.
     * @param height The height of the window.
     *
     * @throws std::runtime_error If SDL initialization fails or window creation fails.
     */
    Application::Application(std::string title, int width, int height)
        : _coreManager(Core::CoreManager()), _window(nullptr), _renderer(nullptr), _quit(false),
            _deltaTime(0.0f), _previousFrameTime(0.0f) {
        _coreManager.Init();

        InitSDL(title, width, height);
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
            _window = SDL_CreateWindow(title.data(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    width, height, SDL_WINDOW_RESIZABLE);
            if (_window == nullptr) {
                std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
                SDL_Quit();
                exit(-1);
            }
            else {
                // Create renderer for window
                _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
                if (_renderer == nullptr) {
                    std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
                    SDL_DestroyWindow(_window);
                    SDL_Quit();
                    exit(-1);
                }
                else {
                    // Initialize renderer color
                    SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                    // Initialize TTF
                    if (TTF_Init() < 0) {
                        std::cerr << "TTF could not be initialized! SDL_Error: " << SDL_GetError() << std::endl;
                        SDL_DestroyWindow(_window);
                        SDL_DestroyRenderer(_renderer);
                        SDL_Quit();
                        exit(-1);
                    }
                    else {
                        _surface = SDL_GetWindowSurface(_window);
                        if (_surface == nullptr) {
                            std::cerr << "Surface could not be created! SDL_Error: " << SDL_GetError() << std::endl;
                            SDL_DestroyWindow(_window);
                            SDL_DestroyRenderer(_renderer);
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
     * and _quitting the SDL library.
     *
     * @throws None
     */
    void Application::CleanUpSDL() {
        SDL_DestroyRenderer(_renderer);
        SDL_DestroyWindow(_window);
        SDL_FreeSurface(_surface);
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
    void Application::Run() {
        SDL_Event event;

        InitLayer();

        while (!_quit) {
            //Calculates delta time
            UpdateDeltaTime();

            PreEventLayer();

            //Polls for events
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    _quit = true;
                }
                else {
                    EventLayer(event);
                }
            }

            UpdateLayer(_deltaTime);

            SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x00, 0xFF);
            SDL_RenderClear(_renderer);

            RenderLayer(_renderer, _window, _surface);

            SDL_RenderPresent(_renderer);

            PostRenderLayer();
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
        float newDeltaTime = (currentTime - _previousFrameTime) / 1000.0f;
        _deltaTime = newDeltaTime;
        _previousFrameTime = currentTime;
    }
}