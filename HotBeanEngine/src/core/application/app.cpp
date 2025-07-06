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
        App::App(const std::string& config_path)
            : App(config_path, std::make_shared<DefaultComponentFactory>()) {}

        App::App(const std::string& config_path, std::shared_ptr<IComponentFactory> component_factory)
            : m_component_factory(component_factory), m_window(nullptr), m_renderer(nullptr),
            m_quit(false), m_delta_time(0.0f), m_previous_frame_time(0.0f) {

            _instance = this;

            bool config_loaded = Config::LoadConfig(config_path) == 0;

            // Setup logging first to capture any application initialization errors
            m_logging_manager = std::make_shared<LoggingManager>(Config::LOG_PATH, Config::LOGGING_LEVEL);

            if (config_loaded) {
                LOG_CORE(LoggingType::INFO, "Config file loaded.");
            }
            else {
                LOG_CORE(LoggingType::ERROR, "Failed to load config file at \"" + config_path + "\"");
                LOG_CORE(LoggingType::INFO, "\tLoading Default config");
            }

            // Initialize other core managers
            m_ecs_manager = std::make_shared<ECSManager>(m_logging_manager);
            m_component_factory->SetECSManager(m_ecs_manager);
            m_component_factory->RegisterComponents();
            m_serialization_manager = std::make_unique<SerializationManager>(m_ecs_manager, m_logging_manager, m_component_factory);

            // Initialize SDL
            if (SDL_Init(SDL_INIT_VIDEO || SDL_INIT_AUDIO) < 0) {
                LOG_CORE(LoggingType::FATAL, std::string("SDL could not initialize! SDL_Error: ") + SDL_GetError());
                exit(-1);
            }
    
            // Create window
            m_window = SDL_CreateWindow(Config::WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
            if (m_window == nullptr) {
                LOG_CORE(LoggingType::FATAL, std::string("Window could not be created! SDL_Error: ") + SDL_GetError());
                exit(-1);
            }
    
            // Create renderer for window
            m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
            if (m_renderer == nullptr) {
                LOG_CORE(LoggingType::FATAL, std::string("Renderer could not be created! SDL_Error: ") + SDL_GetError());
                exit(-1);
            }
    
            // Initialize renderer color
            SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    
            // Create surface
            m_surface = SDL_GetWindowSurface(m_window);
            if (m_surface == nullptr) {
                LOG_CORE(LoggingType::FATAL, std::string("Surface could not be created! SDL_Error: ") + SDL_GetError());
                exit(-1);
            }
    
            // Initialize TTF
            if (TTF_Init() < 0) {
                LOG_CORE(LoggingType::FATAL, std::string("TTF could not be initialized! TTF_Error: ") + TTF_GetError());
                exit(-1);
            }
    
            // Initialize Audio Mixer
            if (Mix_Init(MIX_INIT_WAVPACK) < 0) {
                LOG_CORE(LoggingType::FATAL, std::string("Audio mixer could not be initialized! Mix_Error: ") + Mix_GetError());
                exit(-1);
            }
            else if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
                LOG_CORE(LoggingType::FATAL, std::string("Audio device could not be opened! Mix_Error: ") + Mix_GetError());
                exit(2);
            }
    
            // Initialize Image
            if (IMG_Init(IMG_INIT_PNG) < 0) {
                LOG_CORE(LoggingType::FATAL, std::string("Image could not be initialized! IMG_Error: ") + IMG_GetError());
                exit(-1);
            }
        }
    
        App::~App() {
            CleanUpSDL();
        }

        App& App::GetInstance() {
            return *_instance;
        }

        // -- Getters and Setters -- //
        SDL_Renderer* App::GetRenderer() const {
            return m_renderer;
        }
        
        void App::SetRenderer(SDL_Renderer* renderer) {
            m_renderer = renderer;
        }

        SDL_Window* App::GetWindow() const {
            return m_window;
        }

        void App::SetWindow(SDL_Window* window) {
            m_window = window;
        }

        SDL_Surface* App::GetSurface() const {
            return m_surface;
        }

        void App::SetSurface(SDL_Surface* surface) {
            m_surface = surface;
        }

        float App::GetDeltaTime() const {
            return m_delta_time;
        }

        std::shared_ptr<ECSManager> App::GetECSManager() const {
            return m_ecs_manager;
        }

        /**
         * @brief Logs a message to a log file.
         * 
         * @param message Message to log to the log file
         */
        void App::Log(LoggingType type, std::string message,
                      const char* file, int line, const char* function) {
            m_logging_manager->Log(type, message, file, line, function);
        }

        void App::SetLoggingLevel(LoggingType level) {
            m_logging_manager->SetLoggingLevel(level);
        }

        void App::SetLogPath(std::string log_path) {
            m_logging_manager->SetLogPath(log_path);
        }
    
        /**
         * @brief Runs the main game loop of the application.
         */
        void App::Run() {
            SDL_Event event;

            OnStart();
    
            while (!m_quit) {
                //Calculates delta time
                UpdateDeltaTime();
    
                OnPreEvent();
    
                //Polls for events
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        m_quit = true;
                    }
                    else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
                        OnWindowResize(event);
                    }
                    else {
                        OnEvent(event);
                    }
                }
    
                // Clear the renderer and prepare for the next frame
                SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0xFF);
                SDL_RenderClear(m_renderer);
    
                OnUpdate();
                OnRender();
    
                // Present the next frame
                SDL_RenderPresent(m_renderer);
    
                OnPostRender();
            }
        }
    
        /**
         * @brief Cleans up the SDL resources by destroying the renderer, window, surface,
         * and m_quitting the SDL library.
         */
        void App::CleanUpSDL() {
            SDL_DestroyRenderer(m_renderer);
            SDL_FreeSurface(m_surface);
            SDL_DestroyWindow(m_window);
     
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
            return m_ecs_manager->CreateEntity();
        }

        void App::DestroyEntity(Entity entity) {
            m_ecs_manager->DestroyEntity(entity);
        }
    
        /**
         * @brief Updates the delta time (time elapsed) between frames.
         */
        void App::UpdateDeltaTime() {
            Uint32 currentTime = SDL_GetTicks();
            float newDeltaTime = (currentTime - m_previous_frame_time) / 1000.0f;
            m_delta_time = newDeltaTime;
            m_previous_frame_time = currentTime;
        }
    
        /**
         * @brief Initializes the application systems and iterates through the
         * systems in the system manager, calling their OnStart methods.
         */
        void App::OnStart() {
            // This is also called when a scene is loaded. (Should this just be removed?)
            m_ecs_manager->IterateSystems(GameLoopState::OnStart);
        }

        /**
         * @brief Calls the OnEvent method of each system in the system manager.
         *
         * @param event The SDL event to be handled.
         */
        void App::OnPreEvent() {
            m_ecs_manager->IterateSystems(GameLoopState::OnPreEvent);
        }
    
        /**
         * @brief Calls the OnEvent method of each system in the system manager.
         *
         * @param event The SDL event to be handled.
         */
        void App::OnEvent(SDL_Event& event) {
            m_ecs_manager->IterateSystems(event, GameLoopState::OnEvent);
        }

        /**
         * @brief Calls the OnWindowResize method of each system in the system manager.
         * 
         */
        void App::OnWindowResize(SDL_Event& event) {
            m_ecs_manager->IterateSystems(event, GameLoopState::OnWindowResize);
        }
    
        /**
         * @brief Calls the OnUpdate method of each system in the system manager.
         *
         * @param renderer The SDL_Renderer to render with.
         * @param delta_time The time in seconds since the last frame.
         */
        void App::OnUpdate() {
            m_ecs_manager->IterateSystems(GameLoopState::OnUpdate);
        }
    
        /**
         * @brief Renders all systems within the application by invoking their OnRender method.
         *
         * @param renderer The SDL_Renderer to render with.
         * @param window The SDL_Window that the renderer is attached to.
         * @param surface The SDL_Surface to render to.
         */
        void App::OnRender() {
            m_ecs_manager->IterateSystems(GameLoopState::OnRender);
        }
    
        /**
         * @brief Calls the OnPostRender method of each system in the system manager.
         * 
         * @param renderer The SDL_Renderer to render with.
         */
        void App::OnPostRender() {
            m_ecs_manager->IterateSystems(GameLoopState::OnPostRender);
        }
    }
}