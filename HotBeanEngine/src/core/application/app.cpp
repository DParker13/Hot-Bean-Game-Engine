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
        App* App::_instance = nullptr;

        /**
         * @brief Constructs an Application instance with the specified window title, width, and height.
         *
         * @param title The title of the application window.
         * @param width The width of the application window.
         * @param height The height of the application window.
         */
        App::App(std::string title, int width, int height)
            : _window(nullptr), _renderer(nullptr), _quit(false),
            _deltaTime(0.0f), _previousFrameTime(0.0f) {

            _instance = this;

            // Setup logging first to capture any application initialization errors
            _logging_manager = std::make_shared<LoggingManager>();
            _logging_manager->SetLogPath(Config::LOG_PATH);
            _logging_manager->SetLoggingLevel(Config::LOGGING_LEVEL);

            // Initialize other core managers
            _ecs_manager = std::make_shared<ECSManager>(_logging_manager);
            _serialization_manager = std::make_unique<SerializationManager>(_ecs_manager, _logging_manager);

            // Initialize SDL
            if (SDL_Init(SDL_INIT_VIDEO || SDL_INIT_AUDIO) < 0) {
                Log(LoggingType::FATAL, std::string("SDL could not initialize! SDL_Error: ") + SDL_GetError());
                exit(-1);
            }
    
            // Create window
            _window = SDL_CreateWindow(title.data(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    width, height, SDL_WINDOW_RESIZABLE);
            if (_window == nullptr) {
                Log(LoggingType::FATAL, std::string("Window could not be created! SDL_Error: ") + SDL_GetError());
                exit(-1);
            }
    
            // Create renderer for window
            _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
            if (_renderer == nullptr) {
                Log(LoggingType::FATAL, std::string("Renderer could not be created! SDL_Error: ") + SDL_GetError());
                exit(-1);
            }
    
            // Initialize renderer color
            SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    
            // Create surface
            _surface = SDL_GetWindowSurface(_window);
            if (_surface == nullptr) {
                Log(LoggingType::FATAL, std::string("Surface could not be created! SDL_Error: ") + SDL_GetError());
                exit(-1);
            }
    
            // Initialize TTF
            if (TTF_Init() < 0) {
                Log(LoggingType::FATAL, std::string("TTF could not be initialized! TTF_Error: ") + TTF_GetError());
                exit(-1);
            }
    
            // Initialize Audio Mixer
            if (Mix_Init(MIX_INIT_WAVPACK) < 0) {
                Log(LoggingType::FATAL, std::string("Audio mixer could not be initialized! Mix_Error: ") + Mix_GetError());
                exit(-1);
            }
            else if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
                Log(LoggingType::FATAL, std::string("Audio device could not be opened! Mix_Error: ") + Mix_GetError());
                exit(2);
            }
    
            // Initialize Image
            if (IMG_Init(IMG_INIT_PNG) < 0) {
                Log(LoggingType::FATAL, std::string("Image could not be initialized! IMG_Error: ") + IMG_GetError());
                exit(-1);
            }
        }
    
        App::~App() {
            CleanUpSDL();
        }

        App& App::GetInstance() {
            return *_instance;
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

        std::shared_ptr<ECSManager> App::GetECSManager() const {
            return _ecs_manager;
        }

        /**
         * @brief Logs a message to a log file.
         * 
         * @param message 
         */
        void App::Log(LoggingType type, std::string message) {
            _logging_manager->Log(type, message);
        }

        void App::SetLoggingLevel(LoggingType level) {
            _logging_manager->SetLoggingLevel(level);
        }

        void App::SetLogPath(std::string log_path) {
            _logging_manager->SetLogPath(log_path);
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
    
            OnStart();
    
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

        Entity App::CreateEntity() {
            return _ecs_manager->CreateEntity();
        }

        void App::DestroyEntity(Entity entity) {
            _ecs_manager->DestroyEntity(entity);
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
        void App::OnStart() {
            SetupSystems();
    
            _ecs_manager->IterateSystems(GameLoopState::OnInit);
        }

        /**
         * @brief Calls the OnEvent method of each system in the system manager.
         *
         * @param event The SDL event to be handled.
         */
        void App::OnPreEvent() {
            _ecs_manager->IterateSystems(GameLoopState::OnPreEvent);
        }
    
        /**
         * @brief Calls the OnEvent method of each system in the system manager.
         *
         * @param event The SDL event to be handled.
         */
        void App::OnEvent(SDL_Event& event) {
            _ecs_manager->IterateSystems(event);
        }
    
        /**
         * @brief Calls the OnUpdate method of each system in the system manager.
         *
         * @param renderer The SDL_Renderer to render with.
         * @param delta_time The time in seconds since the last frame.
         */
        void App::OnUpdate() {
            _ecs_manager->IterateSystems(GameLoopState::OnUpdate);
        }
    
        /**
         * @brief Renders all systems within the application by invoking their OnRender method.
         *
         * @param renderer The SDL_Renderer to render with.
         * @param window The SDL_Window that the renderer is attached to.
         * @param surface The SDL_Surface to render to.
         */
        void App::OnRender() {
            _ecs_manager->IterateSystems(GameLoopState::OnRender);
        }
    
        /**
         * @brief Calls the OnPostRender method of each system in the system manager.
         * 
         * @param renderer The SDL_Renderer to render with.
         */
        void App::OnPostRender() {
            _ecs_manager->IterateSystems(GameLoopState::OnPostRender);
        }
    }
}