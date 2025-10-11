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

#include <HotBeanEngine/application/application.hpp>

namespace HBE::Application {
    Application* Application::s_instance = nullptr;

    /**
     * @brief Construct Application with custom component factory
     * 
     * @param config_path Path to the config file
     * @param component_factory Custom component factory
     */
    Application::Application(const std::string& config_path, std::shared_ptr<IComponentFactory> component_factory)
        : m_component_factory(component_factory), m_window(nullptr), m_renderer(nullptr),
        m_quit(false), m_delta_time(0.0f), m_previous_frame_time(0) {

        s_instance = this;

        bool config_loaded = Config::LoadConfig(config_path) == 0;

        SetupRendererAndWindow();

        // Setup logging first to capture any application initialization errors
        m_logging_manager = std::make_shared<LoggingManager>(Config::LOG_PATH, Config::LOGGING_LEVEL, Config::LOG_TO_CONSOLE);

        if (config_loaded) {
            LOG_CORE(LoggingType::INFO, "Config file loaded.");
        }
        else {
            if (config_path == "Instantiating Application through GetInstance()") {
                LOG_CORE(LoggingType::INFO, "Instantiating Application through GetInstance()");
            }
            else {
                LOG_CORE(LoggingType::ERROR, "Failed to load config file at \"" + config_path + "\"");
            }
            LOG_CORE(LoggingType::INFO, "\tLoading Default config");
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Config Error", std::string("Failed to load config file at \"" + config_path + "\"").data(), m_window);
        }

        // Initialize other core managers
        m_ecs_manager = std::make_shared<ECSManager>(m_logging_manager);
        m_component_factory->SetECSManager(m_ecs_manager);
        m_component_factory->RegisterComponents();
        m_scene_manager = std::make_unique<SceneManager>(m_ecs_manager, m_logging_manager);

        InitSDL();
        InitSDLTTF();
        InitSDLMixer();
    }

    Application::~Application() {
        CleanUpSDL();
        delete s_instance;
        s_instance = nullptr;
    }

    /**
     * @brief Sets up the renderer and window for the application.
     * Cleans up any previously created window surface and renderer before creating a new one.
     */
    void Application::SetupRendererAndWindow() {
        // Clean up previously created renderer if it exists
        if (m_renderer != nullptr) {
            SDL_DestroyRenderer(m_renderer);
            m_renderer = nullptr;
        }

        // Create new window surface
        if (m_window == nullptr) {
            SDL_CreateWindowAndRenderer(Config::WINDOW_TITLE.c_str(), Config::SCREEN_WIDTH,
                                                   Config::SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE,
                                                   &m_window, &m_renderer);

            // Check if window creation was successful
            if (m_window == nullptr) {
                LOG_CORE(LoggingType::FATAL, std::string("Window could not be created! SDL_Error: ") + SDL_GetError());
                exit(-1);
            }

            if (m_renderer == nullptr) {
                LOG_CORE(LoggingType::FATAL, std::string("Renderer could not be created! SDL_Error: ") + SDL_GetError());
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Failed to create renderer", m_window);
                exit(-1);
            }
        }

        // Initialize renderer settings
        SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
        
        // Clear the renderer to prepare for the next frame
        SDL_RenderClear(m_renderer);
    }

    /**
     * @brief Initializes the SDL library and creates the window and renderer.
     */
    void Application::InitSDL() {
        // Initialize SDL
        if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
            LOG_CORE(LoggingType::FATAL, std::string("SDL could not initialize! SDL_Error: ") + SDL_GetError());
            exit(-1);
        }
    }

    /**
     * @brief Initializes the SDL_TTF library.
     */
    void Application::InitSDLTTF() {
        // Initialize TTF
        if (!TTF_Init()) {
            LOG_CORE(LoggingType::FATAL, std::string("TTF could not be initialized! SDL_Error: ") + SDL_GetError());
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Failed to initialize SDL TTF", m_window);
            exit(-1);
        }
    }

    /**
     * @brief Initializes the SDL_Image library.
     */
    // void Application::InitSDLImage() {
    //     // Initialize Image
    //     if (!IMG_Init()) {
    //         LOG_CORE(LoggingType::FATAL, std::string("Image could not be initialized! SDL_Error: ") + SDL_GetError());
    //         SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Failed to initialize SDL Image", m_window);
    //         exit(-1);
    //     }
    // }

    /**
     * @brief Initializes the SDL_Mixer library.
     */
    void Application::InitSDLMixer() {
        // if (!MIX_Init()) {
        //     LOG_CORE(LoggingType::FATAL, std::string("Audio mixer could not be initialized! SDL_Error: ") + SDL_GetError());
        //     SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Failed to initialize SDL Mixer", m_window);
        //     exit(-1);
        // }
        // else if(MIX_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
        //     LOG_CORE(LoggingType::FATAL, std::string("Audio device could not be opened! SDL_Error: ") + SDL_GetError());
        //     SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Mixer Error", "Failed to open audio device", m_window);
        //     exit(-1);
        // }
    }

    Application& Application::GetInstance() {
        if (!s_instance) {
            std::cout << "Application::GetInstance() was called before the application was instantiated properly!" << std::endl;
        }

        return *s_instance;
    }

    // -- Getters and Setters -- //
    SDL_Renderer* Application::GetRenderer() const {
        return m_renderer;
    }
    
    void Application::SetRenderer(SDL_Renderer* renderer) {
        m_renderer = renderer;
    }

    SDL_Window* Application::GetWindow() const {
        return m_window;
    }

    void Application::SetWindow(SDL_Window* window) {
        m_window = window;
    }

    /**
     * @brief Gets the delta time (time elapsed) between frames in seconds.
     */
    float Application::GetDeltaTime() const {
        return m_delta_time;
    }

    /**
     * @brief Gets the high resolution delta time (time elapsed) between frames in seconds.
     */
    double Application::GetDeltaTimeHiRes() const {
        return m_delta_time_hi_res;
    }

    ECSManager& Application::GetECSManager() const {
        return *m_ecs_manager;
    }

    SceneManager& Application::GetSceneManager() const {
        return *m_scene_manager;
    }

    std::shared_ptr<IComponentFactory> Application::GetComponentFactory() const {
        return m_component_factory;
    }

    /**
     * @brief Logs a message to a log file.
     * 
     * @param message Message to log to the log file
     */
    void Application::Log(LoggingType type, std::string message,
                    const char* file, int line, const char* function) {
        m_logging_manager->Log(type, message, file, line, function);
    }

    void Application::SetLoggingLevel(LoggingType level) {
        m_logging_manager->SetLoggingLevel(level);
    }

    void Application::SetLogPath(std::string log_path) {
        m_logging_manager->SetLogPath(log_path);
    }

    /**
     * @brief Starts the main game loop of the application.
     */
    void Application::Start() {
        // Call system OnStart methods
        OnStart();

        while (!m_quit) {
            // Calculates delta time
            UpdateDeltaTime();
            UpdateDeltaTimeHiRes();

            // Handle all events
            EventLoop();

            // Clear the renderer and prepare for the next frame
            SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0xFF);
            SDL_RenderClear(m_renderer);

            // Fixed timestep physics loop
            PhysicsLoop();

            // Call system OnUpdate methods
            OnUpdate();

            // Call system OnRender methods
            OnRender();

            // Present the next frame
            SDL_RenderPresent(m_renderer);

            // Call system OnPostRender methods
            OnPostRender();
        }
    }

    void Application::EventLoop() {
        OnPreEvent();

        //Polls for events
        while (SDL_PollEvent(&event)) {
            // Application level events are handled here. Each system can handle their own events through the OnEvent method
            if (event.type == SDL_EVENT_QUIT) {
                m_quit = true;
            }
            else if (event.type == SDL_EVENT_WINDOW_RESIZED) {
                // Call system OnWindowResize methods
                OnWindowResize(event);
            }
            else {
                // Call system OnEvent methods
                OnEvent(event);
            }
        }
    }

    /**
     * @brief Cleans up the SDL resources by destroying the renderer, window, surface,
     * and m_quitting the SDL library.
     */
    void Application::CleanUpSDL() {
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
    
        // TTF
        TTF_Quit();

        // Audio
        //MIX_CloseAudio();
        //MIX_Quit();

        // Image
        //IMG_Quit();

        // SDL
        SDL_Quit();
    }

    /**
     * @brief Gets the high resolution time in seconds since the application started.
     */
    double Application::GetHiResTime() const {
        static Uint64 start = SDL_GetPerformanceCounter();
        Uint64 now = SDL_GetPerformanceCounter();
        Uint64 freq = SDL_GetPerformanceFrequency();
        return static_cast<double>(now - start) / static_cast<double>(freq);
    }

    /**
     * @brief Updates the delta time (time elapsed) between frames in seconds.
     */
    void Application::UpdateDeltaTime() {
        Uint64 current_time = SDL_GetTicks();
        m_delta_time = static_cast<float>(current_time - m_previous_frame_time) / 1000.0f;

        // Cap delta time
        if (m_delta_time > 0.25f) {
            m_delta_time = 0.25f;
        }

        m_previous_frame_time = current_time;
    }

    /**
     * @brief Updates the high resolution delta time (time elapsed) between frames in seconds.
     */
    void Application::UpdateDeltaTimeHiRes() {
        double current_time = GetHiResTime();
        m_delta_time_hi_res = current_time - m_previous_frame_time_hi_res;

        // Cap frame time to avoid spiral of death
        if (m_delta_time_hi_res > 0.25)
            m_delta_time_hi_res = 0.25;

        m_previous_frame_time_hi_res = current_time;
    }

    /**
     * @brief Updates the fixed delta time for fixed timestep updates.
     */
    void Application::PhysicsLoop() {
        m_accumulator += GetDeltaTimeHiRes();

        // Fixed timestep loop
        while (m_accumulator >= m_fixed_time_step) {
            //m_previousState = m_currentState;
            // Advance your simulation here (e.g., physics, ECS fixed update)
            m_ecs_manager->IterateSystems(GameLoopState::OnFixedUpdate);
            m_physics_sim_time += m_fixed_time_step; // Advance simulation time tracker
            m_accumulator -= m_fixed_time_step;
        }

        // Interpolation factor
        //double alpha = m_accumulator / m_fixed_time_step;

        // Interpolate state for rendering (customize as needed)
        //State renderState = m_currentState * alpha + m_previousState * (1.0 - alpha);
    }

    /**
     * @brief Initializes the application systems and iterates through the
     * systems in the system manager, calling their OnStart methods.
     */
    void Application::OnStart() {
        // This is also called when a scene is loaded. (Should this just be removed?)
        m_ecs_manager->IterateSystems(GameLoopState::OnStart);
    }

    /**
     * @brief Calls the OnEvent method of each system in the system manager.
     *
     * @param event The SDL event to be handled.
     */
    void Application::OnPreEvent() {
        m_ecs_manager->IterateSystems(GameLoopState::OnPreEvent);
    }

    /**
     * @brief Calls the OnEvent method of each system in the system manager.
     *
     * @param event The SDL event to be handled.
     */
    void Application::OnEvent(SDL_Event& event) {
        m_ecs_manager->IterateSystems(event, GameLoopState::OnEvent);
    }

    /**
     * @brief Calls the OnWindowResize method of each system in the system manager.
     * 
     * @param event The SDL event to be handled.
     */
    void Application::OnWindowResize(SDL_Event& event) {
        m_ecs_manager->IterateSystems(event, GameLoopState::OnWindowResize);
    }

    /**
     * @brief Calls the OnUpdate method of each system in the system manager.
     *
     * @param renderer The SDL_Renderer to render with.
     * @param delta_time The time in seconds since the last frame.
     */
    void Application::OnUpdate() {
        m_ecs_manager->IterateSystems(GameLoopState::OnUpdate);
    }

    /**
     * @brief Renders all systems within the application by invoking their OnRender method.
     *
     * @param renderer The SDL_Renderer to render with.
     * @param window The SDL_Window that the renderer is attached to.
     * @param surface The SDL_Surface to render to.
     */
    void Application::OnRender() {
        m_ecs_manager->IterateSystems(GameLoopState::OnRender);
    }

    /**
     * @brief Calls the OnPostRender method of each system in the system manager.
     * 
     * @param renderer The SDL_Renderer to render with.
     */
    void Application::OnPostRender() {
        m_ecs_manager->IterateSystems(GameLoopState::OnPostRender);
    }
}