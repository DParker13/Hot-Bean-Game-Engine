/**
 * @file application.cpp
 * @author Daniel Parker (DParker13)
 * @brief Main entry point of the application.
 * Initializes SDL, creates the window and renderer, and manages the main game loop.
 * @version 0.1
 * @date 2025-02-18
 *
 * @copyright Copyright (c) 2025
 */

#include <iostream>

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/editor/editor_gui.hpp>
#include <HotBeanEngine/editor/noop_editor_gui.hpp>

namespace HBE::Application {
    using namespace Core;
    using namespace Managers;
    using namespace Listeners;
    using namespace Factories;

    Application::Application(std::shared_ptr<IComponentFactory> component_factory,
                             std::shared_ptr<ISystemFactory> system_factory,
                             std::shared_ptr<ISceneFactory> scene_factory)
        : m_component_factory(component_factory), m_system_factory(system_factory), m_scene_factory(scene_factory) {

        // Setup singleton instance
        s_instance = this;

        m_serialization_manager = std::make_shared<SerializationManager>();

#if !GAME_RELEASE_BUILD
        int config_load_result = LoadConfig();
#endif

        // Setup logging first to capture any application initialization errors
        // TODO: Initialize logging manager sooner, but queue the logs until a directory is available
        m_logging_manager = std::make_shared<LoggingManager>(g_config.GetLogDirectory(), g_config.GetLoggingLevel(),
                                                             g_config.GetLogToConsole());

#if !GAME_RELEASE_BUILD
        if (config_load_result != 0) {
            LOG_CORE(LoggingType::WARNING, "Failed to load config file, using defaults.");
        }
#endif

        SetupRendererAndWindow();

        // Initialize input event listener
        m_input_event_listener = std::make_unique<Listeners::InputEventListener>(m_logging_manager);

        // Initialize application parts and layers
        InitEditor();
        InitManagers();
        InitSDL();
        InitSDLTTF();
        InitSDLMixer();

        // Register component listeners for OnComponentAdded and OnComponentRemoved events
        RegisterComponentListeners();

        m_editor_gui->OnApplicationReady();
    }

    Application::~Application() {
        // Ensure scenes/systems are destroyed before SDL subsystems are torn down.
        // TODO: In editor mode, this should ask the user if they want to save the current scene before quitting.
        if (m_scene_manager && GetSceneManager().GetCurrentScene()) {
            GetSceneManager().UnloadScene();
        }

        m_scene_manager.reset();
        m_loop_manager.reset();
        m_ecs_manager.reset();
        m_event_manager.reset();
        m_audio_manager.reset();
        m_transform_manager.reset();
        m_camera_manager.reset();
        m_render_manager.reset();
        m_input_event_listener.reset();
        m_editor_gui.reset();

        CleanUpSDL();
        s_instance = nullptr;
    }

    void Application::SetupRendererAndWindow() {
        // Create new window surface
        if (m_window == nullptr) {
            SDL_CreateWindowAndRenderer("Hot Bean Engine", 1280, 720, SDL_WINDOW_RESIZABLE, &m_window, &m_renderer);

            // Check if window creation was successful
            if (m_window == nullptr) {
                LOG_CORE(LoggingType::FATAL, std::string("Window could not be created! SDL_Error: ") + SDL_GetError());
                exit(-1);
            }

            if (m_renderer == nullptr) {
                LOG_CORE(LoggingType::FATAL,
                         std::string("Renderer could not be created! SDL_Error: ") + SDL_GetError());
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

    void Application::InitManagers() {
        m_ecs_manager = std::make_shared<ECSManager>(m_logging_manager);

        // Setup component and system factories
        m_component_factory->SetECSManager(m_ecs_manager);
        m_component_factory->RegisterComponents();
        m_system_factory->RegisterSystems();
        // m_scene_factory->RegisterScenes();

        m_scene_manager = std::make_unique<SceneManager>();
        m_loop_manager = std::make_unique<StateManager>();
        m_camera_manager = std::make_shared<CameraManager>();
        m_render_manager = std::make_shared<RenderManager>(m_camera_manager);
        m_transform_manager = std::make_shared<TransformManager>();
        m_event_manager = std::make_shared<EventManager>();
    }

    void Application::InitSDL() {
        // Initialize SDL
        if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
            LOG_CORE(LoggingType::FATAL, std::string("SDL could not initialize! SDL_Error: ") + SDL_GetError());
            exit(-1);
        }
    }

    void Application::InitSDLTTF() {
        // Initialize TTF
        if (!TTF_Init()) {
            LOG_CORE(LoggingType::FATAL, std::string("TTF could not be initialized! SDL_Error: ") + SDL_GetError());
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Failed to initialize SDL TTF", m_window);
            exit(-1);
        }
    }

    // Unused: SDL_Image initialization
    // void Application::InitSDLImage() {
    //     // Initialize Image
    //     if (!IMG_Init()) {
    //         LOG_CORE(LoggingType::FATAL, std::string("Image could not be initialized! SDL_Error: ") +
    //         SDL_GetError()); SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Failed to initialize SDL
    //         Image", m_window); exit(-1);
    //     }
    // }

    void Application::InitSDLMixer() {
        if (!MIX_Init()) {
            LOG_CORE(LoggingType::FATAL,
                     std::string("Audio mixer could not be initialized! SDL_Error: ") + SDL_GetError());
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Failed to initialize SDL Mixer", m_window);
            exit(-1);
        }
        // else if(MIX_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
        //     LOG_CORE(LoggingType::FATAL, std::string("Audio device could not be opened! SDL_Error: ") +
        //     SDL_GetError()); SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Mixer Error", "Failed to open audio
        //     device", m_window); exit(-1);
        // }
    }

    void Application::RegisterComponentListeners() {
        GetECSManager().RegisterComponentListener(&GetRenderManager());
        GetECSManager().RegisterComponentListener(&GetTransformManager());
    }

    void Application::InitEditor() {
#if GAME_RELEASE_BUILD
        m_editor_gui = std::make_unique<Editor::NoopEditorGUI>();
#else
        m_editor_gui = std::make_unique<Editor::EditorGUI>();
        GetLoggingManager().RegisterLogListener(m_editor_gui.get());
        m_editor_gui->InitEditorGUI();
#endif
    }

    Application &Application::GetInstance() {
        if (!s_instance) {
            std::cout << "Application::GetInstance() was called before the application was instantiated properly!"
                      << std::endl;
        }

        return *s_instance;
    }

    // -- Getters and Setters -- //
    void Application::Log(LoggingType type, std::string_view message, const char *file, int line,
                          const char *function) {
        GetLoggingManager().Log(type, message, file, line, function);
    }

    void Application::SetLoggingLevel(LoggingType level) {
        g_config.SetLoggingLevel(level);
        GetLoggingManager().SetLoggingLevel(level);
    }

    void Application::SetLogDirectory(std::filesystem::path log_directory) {
        g_config.SetLogDirectory(log_directory);
        GetLoggingManager().SetLogDirectory(log_directory);
    }

    int Application::LoadConfig() {
        try {
            std::shared_ptr<ISerializer> serializer = GetSerializationManager().GetSerializer("BasicSerializer");
            if (serializer->FileExists(CONFIG_DIRECTORY / CONFIG_NAME)) {
                serializer->Deserialize(CONFIG_DIRECTORY / CONFIG_NAME, g_config);
            }
            else {
                return -1;
            }
            return 0;
        } catch (...) {
            return -1;
        }
    }

    void Application::SaveConfig() {
        std::shared_ptr<ISerializer> serializer = GetSerializationManager().GetSerializer("BasicSerializer");
        if (serializer->FileExists(CONFIG_DIRECTORY / CONFIG_NAME)) {
            serializer->Serialize(CONFIG_DIRECTORY / CONFIG_NAME, g_config);
        }
        else {
            LOG(LoggingType::WARNING, "Config file could not be found");
        }
    }

    void Application::Start() {
        // If using NoopEditorGUI, automatically start in Playing state
        if (dynamic_cast<Editor::NoopEditorGUI *>(m_editor_gui.get()) != nullptr) {
            GetStateManager().QueueStateChange(ApplicationState::Playing);
        }

        OnStart();

        while (!m_quit) {
            GetStateManager().UpdateGameLoopState();

            if (GetStateManager().IsState(ApplicationState::Playing) && GetStateManager().ShouldReloadScene()) {
                std::shared_ptr<IScene> current_scene = GetSceneManager().GetCurrentScene();
                if (!current_scene) {
                    LOG(LoggingType::WARNING, "No current scene to reload.");
                }
                else {
                    GetSceneManager().UnloadScene();
                    GetSceneManager().LoadScene(current_scene);
                }

                GetStateManager().ClearReloadFlag();
            }

            UpdateDeltaTime();
            UpdateDeltaTimeHiRes();

            EventLoop();

            // Clear the renderer and prepare for the next frame
            SDL_SetRenderTarget(m_renderer, nullptr);
            SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
            SDL_RenderClear(m_renderer);

            OnUpdate();
            OnRender();

            // Present the next frame
            SDL_RenderPresent(m_renderer);

            // Clean up after rendering
            OnPostRender();
        }
    }

    void Application::EventLoop() {
        OnPreEvent();

        // Polls for events
        while (SDL_PollEvent(&event)) {
            // Application level events are handled here. Each system can handle their own events through the OnEvent
            // method
            if (event.type == SDL_EVENT_QUIT) {
                m_quit = true;
            }
            else if (event.type == SDL_EVENT_WINDOW_RESIZED) {
                // Call system OnWindowResize methods
                OnWindowResize(event);
            }
            else {
                OnEvent(event);
            }
            switch (event.type) {
            case SDL_EVENT_RENDER_DEVICE_LOST:
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "DEVICE LOST!", "SDL_EVENT_RENDER_DEVICE_LOST",
                                         m_window);
                break;
            case SDL_EVENT_RENDER_DEVICE_RESET:
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "DEVICE RESET!", "SDL_EVENT_RENDER_DEVICE_RESET",
                                         m_window);
                break;
            case SDL_EVENT_RENDER_TARGETS_RESET:
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "TARGETS RESET!", "SDL_EVENT_RENDER_TARGETS_RESET",
                                         m_window);
                break;
            }
        }
    }

    void Application::CleanUpSDL() {
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);

        // TTF
        TTF_Quit();

        // Audio
        MIX_Quit();

        // Image
        // IMG_Quit();

        // SDL
        SDL_Quit();
    }

    void Application::UpdateDeltaTime() {
        Uint64 current_time = SDL_GetTicks();
        m_delta_time = static_cast<float>(current_time - m_previous_frame_time) / 1000.0f;

        // Cap delta time
        if (m_delta_time > 0.25f) {
            m_delta_time = 0.25f;
        }

        m_previous_frame_time = current_time;
    }

    void Application::UpdateDeltaTimeHiRes() {
        double current_time = GetHiResTime();
        m_delta_time_hi_res = current_time - m_previous_frame_time_hi_res;

        // Cap frame time to avoid spiral of death
        if (m_delta_time_hi_res > 0.25)
            m_delta_time_hi_res = 0.25;

        m_previous_frame_time_hi_res = current_time;
    }

    void Application::PhysicsLoop() {
        m_accumulator += GetDeltaTimeHiRes();

        // Fixed timestep loop
        while (m_accumulator >= m_fixed_time_step) {
            // m_previousState = m_currentState;
            //  Advance your simulation here (e.g., physics, ECS fixed update)
            GetECSManager().IterateSystems(GameLoopState::OnFixedUpdate);
            m_physics_sim_time += m_fixed_time_step; // Advance simulation time tracker
            m_accumulator -= m_fixed_time_step;
        }

        // Interpolation factor
        // double alpha = m_accumulator / m_fixed_time_step;

        // Interpolate state for rendering (customize as needed)
        // State renderState = m_currentState * alpha + m_previousState * (1.0 - alpha);
    }

    void Application::OnStart() {
        // This is also called when a scene is loaded. (Should this just be removed?)
        GetECSManager().IterateSystems(GameLoopState::OnStart);
    }

    void Application::OnPreEvent() {
        if (GetStateManager().IsState(ApplicationState::Playing)) {
            GetECSManager().IterateSystems(GameLoopState::OnPreEvent);
        }
    }

    void Application::OnEvent(SDL_Event &event) {
        m_input_event_listener->OnEvent(event);

        // Call system OnEvent methods
        if (GetStateManager().IsState(ApplicationState::Playing)) {
            GetECSManager().IterateSystems(event, GameLoopState::OnEvent);
        }

        m_editor_gui->OnEvent(event);
    }

    void Application::OnWindowResize(SDL_Event &event) {
        GetECSManager().IterateSystems(event, GameLoopState::OnWindowResize);

        GetRenderManager().OnWindowResize(event);
        m_editor_gui->OnWindowResize(event);
    }

    void Application::OnUpdate() {
        GetTransformManager().OnUpdate();

        if (GetStateManager().IsState(ApplicationState::Playing)) {
            PhysicsLoop();
            GetECSManager().IterateSystems(GameLoopState::OnUpdate);
        }
        else {
            m_editor_gui->OnUpdate();
        }

        m_input_event_listener->OnUpdate();
    }

    void Application::OnRender() {
        GetECSManager().IterateSystems(GameLoopState::OnRender);

        GetRenderManager().OnRender();
        m_editor_gui->OnRender();
    }

    void Application::OnPostRender() {
        GetECSManager().IterateSystems(GameLoopState::OnPostRender);

        GetRenderManager().OnPostRender();

        // Dispatch all queued events at the end of the frame
        GetEventManager().DispatchAll();
    }
} // namespace HBE::Application