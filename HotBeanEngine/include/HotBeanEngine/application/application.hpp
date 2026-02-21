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
#include <SDL3_ttf/SDL_ttf.h>

#include <HotBeanEngine/application/component_factory.hpp>
#include <HotBeanEngine/application/input_event_listener.hpp>
#include <HotBeanEngine/application/macros.hpp>
#include <HotBeanEngine/application/managers/application_state_manager.hpp>
#include <HotBeanEngine/application/managers/audio_manager.hpp>
#include <HotBeanEngine/application/managers/camera_manager.hpp>
#include <HotBeanEngine/application/managers/ecs_manager.hpp>
#include <HotBeanEngine/application/managers/render_manager.hpp>
#include <HotBeanEngine/application/managers/scene_manager.hpp>
#include <HotBeanEngine/application/managers/transform_manager.hpp>
#include <HotBeanEngine/editor/ieditor_gui.hpp>

namespace HBE::Application {
    using HBE::Core::LoggingType;

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
        inline static Application *s_instance = nullptr; ///< Singleton instance pointer
        SDL_Event event;                                 ///< SDL event used for polling in the event loop

    protected:
        std::shared_ptr<Managers::ECSManager> m_ecs_manager;               ///< Manages entity-component-system
        std::shared_ptr<Managers::LoggingManager> m_logging_manager;       ///< Manages application logging
        std::unique_ptr<Managers::SceneManager> m_scene_manager;           ///< Manages scene loading/switching
        std::unique_ptr<Managers::ApplicationStateManager> m_loop_manager; ///< Manages application state transitions
        std::shared_ptr<Managers::RenderManager> m_render_manager;         ///< Manages rendering operations
        std::shared_ptr<Managers::CameraManager> m_camera_manager;         ///< Manages camera system
        std::shared_ptr<Managers::TransformManager> m_transform_manager;   ///< Manages transform hierarchy
        std::shared_ptr<Managers::AudioManager> m_audio_manager;           ///< Manages audio playback
        std::shared_ptr<IComponentFactory> m_component_factory;            ///< Factory for component creation
        SDL_Renderer *m_renderer = nullptr;                                ///< SDL renderer instance
        SDL_Window *m_window = nullptr;                                    ///< SDL window instance
        std::unique_ptr<GUI::IEditorGUI> m_editor_gui = nullptr;           ///< Editor GUI interface
        std::unique_ptr<InputEventListener> m_input_event_listener;        ///< Handles input events

    public:
        bool m_quit = false; ///< Flag to quit the application

        // Time
        float m_delta_time = 0.0f;        ///< Time elapsed between frames in seconds
        Uint64 m_previous_frame_time = 0; ///< Previous frame time

        // Physics timing
        double m_physics_sim_time = 0.0;           ///< Time for physics updates
        const double m_fixed_time_step = 0.01;     ///< Fixed timestep duration in seconds
        double m_delta_time_hi_res = 0.0;          ///< High resolution delta time between frames in seconds
        double m_previous_frame_time_hi_res = 0.0; ///< Previous frame time in high resolution
        double m_accumulator = 0.0;                ///< Accumulator for fixed timestep updates

        /**
         * @brief Construct the Application instance.
         * @param config_path Path to the configuration YAML file.
         * @param component_factory Factory for creating and registering components.
         * @param editor_gui Optional editor GUI instance (uses NoopEditorGUI if nullptr).
         *
         * Initializes SDL, managers, and sets up the application singleton.
         */
        Application(const std::string &config_path, std::shared_ptr<IComponentFactory> component_factory,
                    std::unique_ptr<GUI::IEditorGUI> editor_gui = nullptr);

        /**
         * @brief Destroy the Application instance and clean up resources.
         */
        ~Application();

        /// @brief Copy constructor (deleted - singleton pattern).
        Application(const Application &) = delete;

        /// @brief Copy assignment operator (deleted - singleton pattern).
        Application &operator=(const Application &) = delete;

        /**
         * @brief Get the singleton Application instance.
         * @return Reference to the Application singleton.
         *
         * @warning Returns a reference that assumes the instance exists.
         * Ensure Application is constructed before calling this.
         */
        static Application &GetInstance();

        // Getters and Setters
        /**
         * @brief Access the SDL renderer owned by the application.
         * @return SDL_Renderer pointer (owned by Application).
         */
        SDL_Renderer *GetRenderer();

        /**
         * @brief Access the SDL window owned by the application.
         * @return SDL_Window pointer (owned by Application).
         */
        SDL_Window *GetWindow();

        /**
         * @brief Get the float delta time between frames (capped at 0.25s).
         * @return Delta time in seconds as a float.
         */
        float GetDeltaTime() const;

        /**
         * @brief Get the high-resolution delta time between frames (capped at 0.25s).
         * @return Delta time in seconds as a double.
         */
        double GetDeltaTimeHiRes() const;

        /**
         * @brief Get elapsed time since start using SDL high-resolution timer.
         * @return Elapsed time in seconds.
         */
        double GetHiResTime() const;

        /**
         * @brief Get the ECS manager facade.
         * @return Reference to the ECS manager.
         */
        Managers::ECSManager &GetECSManager() const;

        /**
         * @brief Access the scene manager.
         * @return Reference to the scene manager.
         */
        Managers::SceneManager &GetSceneManager() const;

        /**
         * @brief Access the application state manager.
         * @return Reference to the application state manager.
         */
        Managers::ApplicationStateManager &GetStateManager() const;

        /**
         * @brief Access the render manager.
         * @return Reference to the render manager.
         */
        Managers::RenderManager &GetRenderManager() const;

        /**
         * @brief Access the camera manager.
         * @return Reference to the camera manager.
         */
        Managers::CameraManager &GetCameraManager() const;

        /**
         * @brief Access the transform manager.
         * @return Reference to the transform manager.
         */
        Managers::TransformManager &GetTransformManager() const;

        /**
         * @brief Access the audio manager.
         * @return Reference to the audio manager.
         */
        Managers::AudioManager &GetAudioManager() const;

        /**
         * @brief Access the component factory.
         * @return Shared pointer to the component factory.
         */
        std::shared_ptr<IComponentFactory> GetComponentFactory() const;

        /**
         * @brief Access the input event listener.
         * @return Reference to the input event listener.
         */
        InputEventListener &GetInputEventListener();

        /**
         * @brief Access the input event listener (const version).
         * @return Const reference to the input event listener.
         */
        const InputEventListener &GetInputEventListener() const;

        /**
         * @brief Access the editor GUI.
         * @return Reference to the editor GUI interface.
         */
        GUI::IEditorGUI &GetEditorGUI();

        /**
         * @brief Log a message with file, line, and function information.
         * @param type The logging type (INFO, WARNING, ERROR, etc.).
         * @param message The message to log.
         * @param file The source file name.
         * @param line The line number.
         * @param function The function name.
         */
        void Log(LoggingType type, std::string_view message, const char *file, int line, const char *function);

        /**
         * @brief Set the logging level threshold.
         * @param level The minimum logging level to output.
         */
        void SetLoggingLevel(LoggingType level);

        /**
         * @brief Set the path for the log file.
         * @param log_path The path to the log file.
         */
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
        /**
         * @brief Called once at the start of the application.
         *
         * Override this to initialize game-specific logic.
         */
        virtual void OnStart();

        /**
         * @brief Called before handling events each frame.
         *
         * Override this for pre-event processing logic.
         */
        virtual void OnPreEvent();

        /**
         * @brief Called when an SDL event occurs.
         * @param event The SDL event to handle.
         *
         * Override this to handle custom events.
         */
        virtual void OnEvent(SDL_Event &event);

        /**
         * @brief Called when the window is resized.
         * @param event The SDL window event containing resize information.
         *
         * Override this to handle window resize logic.
         */
        virtual void OnWindowResize(SDL_Event &event);

        /**
         * @brief Update system and entity game states.
         *
         * Called every frame to update game logic.
         */
        virtual void OnUpdate();

        /**
         * @brief Called to render the scene to the screen.
         *
         * Override this to add custom rendering logic.
         */
        virtual void OnRender();

        /**
         * @brief Called after rendering each frame.
         *
         * Override this for post-render processing.
         */
        virtual void OnPostRender();

    private:
        /// @brief Initialize SDL renderer and window.
        void SetupRendererAndWindow();

        /// @brief Clean up and destroy SDL resources.
        void CleanUpSDL();

        /// @brief Initialize all core managers (ECS, Scene, State, etc.).
        void InitManagers();

        /// @brief Initialize SDL subsystems.
        void InitSDL();

        /// @brief Initialize SDL_TTF (TrueType font) library.
        void InitSDLTTF();

        /// @brief Initialize SDL_Mixer (audio) library.
        void InitSDLMixer();

        /// @brief Register component listeners.
        void RegisterComponentListeners();

        /// @brief Run fixed timestep physics updates.
        void PhysicsLoop();

        /// @brief Process SDL events from the event queue.
        void EventLoop();

        /// @brief Update the float delta time value.
        void UpdateDeltaTime();

        /// @brief Update the high-resolution delta time value.
        void UpdateDeltaTimeHiRes();
    };
} // namespace HBE::Application