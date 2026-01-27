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
#include <HotBeanEngine/application/managers/game_loop_manager.hpp>
#include <HotBeanEngine/application/component_factory.hpp>
#include <HotBeanEngine/application/macros.hpp>
#include <HotBeanEngine/application/input_event_listener.hpp>
#include <HotBeanEngine/editor/ieditor_gui.hpp>

namespace HBE::Application {
    using namespace HBE::Core;
    using namespace HBE::Application::Managers;

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

    protected:
        std::shared_ptr<Managers::ECSManager> m_ecs_manager;
        std::shared_ptr<Managers::LoggingManager> m_logging_manager;
        std::unique_ptr<Managers::SceneManager> m_scene_manager;
        std::unique_ptr<Managers::GameLoopManager> m_loop_manager; ///< Manages game loop state transitions
        std::shared_ptr<IComponentFactory> m_component_factory;
        SDL_Renderer* m_renderer = nullptr;
        SDL_Window* m_window = nullptr;
        std::unique_ptr<GUI::IEditorGUI> m_editor_gui = nullptr;
        InputEventListener m_input_event_listener;

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
        Application(const std::string& config_path, std::shared_ptr<IComponentFactory> component_factory, std::unique_ptr<GUI::IEditorGUI> editor_gui = nullptr);
        ~Application();
        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;

        // Singleton
        static Application& GetInstance();

        // Getters and Setters
        SDL_Renderer* GetRenderer();
        SDL_Window* GetWindow();
        float GetDeltaTime() const;
        double GetDeltaTimeHiRes() const;
        double GetHiResTime() const;
        Managers::ECSManager& GetECSManager() const;
        Managers::SceneManager& GetSceneManager() const;
        Managers::GameLoopManager& GetLoopManager() const;
        std::shared_ptr<IComponentFactory> GetComponentFactory() const;
        InputEventListener& GetInputEventListener();
        const InputEventListener& GetInputEventListener() const;

        // Logging
        void Log(LoggingType type, std::string_view message,
                const char* file, int line, const char* function);
        void SetLoggingLevel(LoggingType level);
        void SetLogPath(std::string_view log_path);

        /**
         * @brief Entry point for the main loop of the application.
         */
        void Start();

        /**
         * @brief Start/play the game.
         * Transitions from Stopped or Paused to Playing state.
         */
        void PlayGame();

        /**
         * @brief Pause the game.
         * Transitions from Playing to Paused state while keeping the scene rendered.
         */
        void PauseGame();

        /**
         * @brief Stop and reset the game.
         * Transitions to Stopped state and marks the scene for reload on next play.
         */
        void StopGame();

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
        void SetupRendererAndWindow();
        void CleanUpSDL();
        void InitManagers();
        void InitSDL();
        void InitSDLTTF();
        void InitSDLMixer();
        void PhysicsLoop();
        void EventLoop();
        void UpdateDeltaTime();
        void UpdateDeltaTimeHiRes();
    };
}