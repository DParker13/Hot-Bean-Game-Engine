/**
 * @file application.cpp
 * @author Daniel Parker (DParker13)
 * @brief Main entry point of the application.
 * Initializes SDL, creates the window and renderer, and manages the main game loop.
 * @version 0.1
 * @date 2025-02-18
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "app.hpp"

namespace Core {
    namespace Application {
        /**
         * @brief Constructs an Application instance with the specified window title, width, and height.
         *
         * @param title The title of the application window.
         * @param width The width of the application window.
         * @param height The height of the application window.
         */
        App::App(std::string title, int width, int height)
            : _coreManager(CoreManager(static_cast<App&>(*this))), _window(nullptr), _renderer(nullptr),
              _quit(false), _deltaTime(0.0f), _previousFrameTime(0.0f) {
            // Initialize SDL
            if (SDL_Init(SDL_INIT_VIDEO || SDL_INIT_AUDIO) < 0) {
                std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
                exit(-1);
            }
    
            // Create window
            _window = SDL_CreateWindow(title.data(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    width, height, SDL_WINDOW_RESIZABLE);
            if (_window == nullptr) {
                std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
                exit(-1);
            }
    
            // Create renderer for window
            _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
            if (_renderer == nullptr) {
                std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
                exit(-1);
            }
    
            // Initialize renderer color
            SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    
            // Create surface
            _surface = SDL_GetWindowSurface(_window);
            if (_surface == nullptr) {
                std::cerr << "Surface could not be created! SDL_Error: " << SDL_GetError() << std::endl;
                exit(-1);
            }
    
            // Initialize TTF
            if (TTF_Init() < 0) {
                std::cerr << "TTF could not be initialized! TTF_Error: " << TTF_GetError() << std::endl;
                exit(-1);
            }
    
            // Initialize Audio Mixer
            if (Mix_Init(MIX_INIT_WAVPACK) < 0) {
                std::cerr << "Audio mixer could not be initialized! Mix_Error: " << Mix_GetError() << std::endl;
                exit(-1);
            }
            else if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
                printf("Audio device could not be opened (Mix_OpenAudio)! Mix_Error: %s\n", Mix_GetError());
                exit(2);
            }
    
            // Initialize Image
            if (IMG_Init(IMG_INIT_PNG) < 0) {
                std::cerr << "Image could not be initialized! IMG_Error: " << IMG_GetError() << std::endl;
                exit(-1);
            }
        }
    
        App::~App() {
            CleanUpSDL();
        }

        CoreManager& App::GetCoreManager() {
            return _coreManager;
        }

        // Getters and Setters
        SDL_Renderer* App::GetRenderer() const {
            return _renderer;
        }
        
        void App::SetRenderer(SDL_Renderer* renderer) {
            _renderer = renderer;
        }

        SDL_Window* App::GetWindow() const {
            return _window;
        }

        void App::SetWindow(SDL_Window* window) {
            _window = window;
        }

        SDL_Surface* App::GetSurface() const {
            return _surface;
        }

        void App::SetSurface(SDL_Surface* surface) {
            _surface = surface;
        }

        float App::GetDeltaTime() const {
            return _deltaTime;
        }
    
        /**
         * @brief Runs the application main loop.
         *
         * This is responsible for initializing the application,
         * polling for events, calculating the delta time,
         * updating the application state, rendering the application
         * state, and cleaning up after itself.
         */
        void App::Run() {
            SDL_Event event;
    
            OnInit();
    
            while (!_quit) {
                //Calculates delta time
                UpdateDeltaTime();
    
                OnPreEvent();
    
                //Polls for events
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        _quit = true;
                    }
                    else {
                        OnEvent(event);
                    }
                }
    
                // Clear the renderer and prepare for the next frame
                SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x00, 0xFF);
                SDL_RenderClear(_renderer);
    
                OnUpdate();
                OnRender();
    
                // Present the next frame
                SDL_RenderPresent(_renderer);
    
                OnPostRender();
            }
        }
    
        /**
         * @brief Cleans up the SDL resources by destroying the renderer, window, surface,
         * and _quitting the SDL library.
         */
        void App::CleanUpSDL() {
            SDL_DestroyRenderer(_renderer);
            SDL_FreeSurface(_surface);
            SDL_DestroyWindow(_window);
     
            // TTF
            TTF_Quit();
    
            // Audio
            Mix_CloseAudio();
            Mix_Quit();
    
            // Image
            IMG_Quit();
            SDL_Quit();
        }
    
        /**
         * @brief Updates the delta time (time elapsed) between frames.
         */
        void App::UpdateDeltaTime() {
            Uint32 currentTime = SDL_GetTicks();
            float newDeltaTime = (currentTime - _previousFrameTime) / 1000.0f;
            _deltaTime = newDeltaTime;
            _previousFrameTime = currentTime;
        }
    
        /**
         * @brief Initializes the application systems and iterates through the
         * systems in the system manager, calling their OnInit methods.
         */
        void App::OnInit() {
            InitSystems();
    
            _coreManager.IterateSystems(GameLoopState::OnInit);
        }
    
        /**
         * @brief Calls the OnEvent method of each system in the system manager.
         *
         * @param event The SDL event to be handled.
         */
        void App::OnEvent(SDL_Event& event) {
            _coreManager.IterateSystems(event);
        }
    
        /**
         * @brief Calls the OnUpdate method of each system in the system manager.
         *
         * @param renderer The SDL_Renderer to render with.
         * @param delta_time The time in seconds since the last frame.
         */
        void App::OnUpdate() {
            _coreManager.IterateSystems(GameLoopState::OnUpdate);
        }
    
        /**
         * @brief Renders all systems within the application by invoking their OnRender method.
         *
         * @param renderer The SDL_Renderer to render with.
         * @param window The SDL_Window that the renderer is attached to.
         * @param surface The SDL_Surface to render to.
         */
        void App::OnRender() {
            _coreManager.IterateSystems(GameLoopState::OnRender);
        }
    
        /**
         * @brief Calls the OnPostRender method of each system in the system manager.
         * 
         * @param renderer The SDL_Renderer to render with.
         */
        void App::OnPostRender() {
            _coreManager.IterateSystems(GameLoopState::OnPostRender);
        }
    }
}