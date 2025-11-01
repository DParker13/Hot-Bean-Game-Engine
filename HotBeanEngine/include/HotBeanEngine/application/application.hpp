/**
 * @file application.hpp
 * @author Daniel Parker (DParker13)
 * @brief Main interface for the application.
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 */
#pragma once

#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <HotBeanEngine/application/managers/ecs_manager.hpp>
#include <HotBeanEngine/application/managers/scene_manager.hpp>
#include <HotBeanEngine/application/component_factory.hpp>
#include <HotBeanEngine/application/macros.hpp>

#include <HotBeanEngine/editor_gui/editor_gui.hpp>

namespace HBE::Application {
    using namespace HBE::Core;
    using namespace HBE::Application::Managers;

    // Forward declaration
    class EditorGUI;

    // Custom Application classes
    /**
     * @brief Enum representing the state of the application.
     */
    enum class ApplicationState {
        Stopped,    ///< The application is stopped.
        Playing,    ///< The application is playing.
        Paused      ///< The application is paused.
    };

    /**
     * @brief Main application class that manages the game loop and core engine systems
     *
     * The Application class implements the singleton pattern and serves as the primary controller
     * for the Hot Bean Engine. It manages:
     * - Window and renderer initialization/cleanup
     * - Game loop and event handling
     * - Core managers (ECS, Scene, Logging)
     * - Editor GUI integration
     * - Physics timing and updates
     * 
     * @note This class follows the singleton pattern and cannot be copied
     * @see IGameLoop and ApplicationState
     */
    class Application : public Core::IGameLoop {
    private:
        inline static Application* s_instance = nullptr; // singleton instance
        SDL_Event event; // Used for polling events in the event loop
        ApplicationState m_state = ApplicationState::Stopped;

    protected:
        std::shared_ptr<Managers::ECSManager> m_ecs_manager;
        std::shared_ptr<Managers::LoggingManager> m_logging_manager;
        std::shared_ptr<IComponentFactory> m_component_factory;
        std::unique_ptr<Managers::SceneManager> m_scene_manager;
        SDL_Renderer* m_renderer = nullptr;
        SDL_Window* m_window = nullptr;
        std::shared_ptr<GUI::EditorGUI> m_editor_gui;

    public:
        bool m_quit = false; ///< Flag to quit the application

        // Time
        float m_delta_time = 0.0f; ///< Time elapsed between frames in seconds
        Uint64 m_previous_frame_time = 0; ///< Previous frame time

        // Physics timing
        double m_physics_sim_time = 0.0; ///< Time for physics updates
        const double m_fixed_time_step = 0.01; ///< Fixed timestep duration in seconds
        double m_delta_time_hi_res = 0.0; ///< High resolution delta time between frames in seconds
        double m_previous_frame_time_hi_res = 0.0; ///< Previous frame time in high resolution
        double m_accumulator = 0.0; ///< Accumulator for fixed timestep updates

        // Constructors
        Application(const std::string& config_path, std::shared_ptr<IComponentFactory> component_factory);
        ~Application();
        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;

        // Singleton
        static Application& GetInstance();

        // Getters and Setters
        ApplicationState& GetState();
        SDL_Renderer* GetRenderer();
        SDL_Window* GetWindow();
        float GetDeltaTime() const;
        double GetDeltaTimeHiRes() const;
        double GetHiResTime() const;
        Managers::ECSManager& GetECSManager() const;
        Managers::SceneManager& GetSceneManager() const;
        std::shared_ptr<IComponentFactory> GetComponentFactory() const;

        // Logging
        void Log(LoggingType type, std::string_view message,
                const char* file, int line, const char* function);
        void SetLoggingLevel(LoggingType level);
        void SetLogPath(std::string_view log_path);

        /**
         * @brief Entry point for the main loop of the application.
         */
        void Start();
        void SetupRendererAndWindow();

    protected:
        // GameLoop Interface
        /// @brief Called once at the start of the game.
        virtual void OnStart();

        /// @brief Called before handling events.
        virtual void OnPreEvent();

        /// @brief Called when an event occurs.
        /// @param event The SDL event to handle.
        virtual void OnEvent(SDL_Event& event);

        /// @brief Called when the window is resized.
        /// @param event The SDL event to handle.
        virtual void OnWindowResize(SDL_Event& event);

        /// @brief Update system and entity game states.
        virtual void OnUpdate();

        /// @brief Called to prepare the screen for rendering.
        virtual void OnRender();

        /// @brief Called after rendering each frame.
        virtual void OnPostRender();

    private:
        void CleanUpSDL();
        void InitManagers();
        void InitSDL();
        void InitSDLTTF();
        void InitSDLMixer();
        void InitGUI();
        void PhysicsLoop();
        void EventLoop();
        void UpdateDeltaTime();
        void UpdateDeltaTimeHiRes();
    };
}