/**
 * @file application.hpp
 * @author Daniel Parker (DParker13)
 * @brief Main interface for the application.
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#pragma once

#include <SDL3_image/SDL_image.h>
//#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <HotBeanEngine/application/managers/ecs_manager.hpp>
#include <HotBeanEngine/application/managers/scene_manager.hpp>
#include <HotBeanEngine/application/component_factory.hpp>
#include <HotBeanEngine/application/macros.hpp>

using namespace HBE::Application::Managers;
using namespace HBE::Core;

namespace HBE::Application {
    // Macros
    #define g_app HBE::Application::Application::GetInstance()
    #define g_ecs g_app.GetECSManager()
    #define LOG(type, message) \
        g_app.Log(type, message, __FILE__, __LINE__, __func__)

    /**
     * @brief Interface for all Application layers ordered in calling order
     */
    class Application : public GameLoop {
        private:
            static Application* s_instance; // singleton of the application
            SDL_Event event; // Used for polling events in the event loop

        protected:
            std::shared_ptr<ECSManager> m_ecs_manager;
            std::shared_ptr<LoggingManager> m_logging_manager;
            std::shared_ptr<IComponentFactory> m_component_factory;
            std::unique_ptr<SceneManager> m_scene_manager;
            SDL_Renderer* m_renderer = nullptr;
            SDL_Window* m_window = nullptr;

        public:
            bool m_quit; ///< Flag to quit the application

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
            SDL_Renderer* GetRenderer() const;
            void SetRenderer(SDL_Renderer* renderer);
            SDL_Window* GetWindow() const;
            void SetWindow(SDL_Window* window);
            float GetDeltaTime() const;
            double GetDeltaTimeHiRes() const;
            double GetHiResTime() const;
            ECSManager& GetECSManager() const;
            SceneManager& GetSceneManager() const;
            std::shared_ptr<IComponentFactory> GetComponentFactory() const;

            // Logging
            void Log(LoggingType type, std::string message,
                    const char* file, int line, const char* function);
            void SetLoggingLevel(LoggingType level);
            void SetLogPath(std::string log_path);

            /**
             * @brief Entry point for the main loop of the application.
             */
            void Start();
            void SetupRendererAndWindow();

        protected:
            // GameLoop Interface
            /**
             * @brief Called once at the start of the game.
             */
            virtual void OnStart();

            /**
             * @brief Called before handling events.
             */
            virtual void OnPreEvent();

            /**
             * @brief Called when an event occurs.
             * 
             * @param event The SDL event to handle.
             */
            virtual void OnEvent(SDL_Event& event);

            /**
             * @brief Called when the window is resized.
             */
            virtual void OnWindowResize(SDL_Event& event);

            /**
             * @brief Called after handling events. Meant to update system and entity game states.
             */
            virtual void OnUpdate();

            /**
             * @brief Called to prepare the screen for rendering.
             */
            virtual void OnRender();

            /**
             * @brief Called after rendering each frame.
             */
            virtual void OnPostRender();

        private:
            void CleanUpSDL();
            void InitSDL();
            void InitSDLTTF();
            void InitSDLMixer();
            void PhysicsLoop();
            void EventLoop();
            void UpdateDeltaTime();
            void UpdateDeltaTimeHiRes();
    };
}