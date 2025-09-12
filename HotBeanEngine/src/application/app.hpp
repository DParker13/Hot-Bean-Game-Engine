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

#include <vector>

#include "../managers/all_managers.hpp"
#include "../components/default_component_factory.hpp"

using namespace HBE::Managers;
using namespace HBE::Core;

namespace HBE::Application {
    // Macros
    #define g_app App::GetInstance()
    #define g_ecs g_app.GetECSManager()
    #define LOG(type, message) \
        g_app.Log(type, message, __FILE__, __LINE__, __func__)

    /**
     * @brief Interface for all Application layers ordered in calling order
     */
    class App : public GameLoop {
        private:
            static App* s_instance; // singleton of the application
            SDL_Event event; // Used for polling events in the event loop

        protected:
            std::shared_ptr<ECSManager> m_ecs_manager;
            std::shared_ptr<LoggingManager> m_logging_manager;
            std::shared_ptr<IComponentFactory> m_component_factory;
            std::unique_ptr<SerializationManager> m_serialization_manager;
            SDL_Renderer* m_renderer = nullptr;
            SDL_Window* m_window = nullptr;
            float m_delta_time; ///< Time elapsed between frames
            float m_previous_frame_time; ///< Previous frame time

        public:
            bool m_quit; ///< Flag to quit the application

            // Constructors
            App(const std::string& config_path);
            App(const std::string& config_path, std::shared_ptr<IComponentFactory> component_factory);
            ~App();
            App(const App&) = delete;
            App& operator=(const App&) = delete;

            // Singleton
            static App& GetInstance();

            // Getters and Setters
            SDL_Renderer* GetRenderer() const;
            void SetRenderer(SDL_Renderer* renderer);
            SDL_Window* GetWindow() const;
            void SetWindow(SDL_Window* window);
            SDL_Surface* GetSurface() const;
            void SetSurface(SDL_Surface* surface);
            float GetDeltaTime() const;
            ECSManager& GetECSManager() const;

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
            /**
             * @brief Cleans up the SDL window and renderer.
             */
            void CleanUpSDL();

            /**
             * @brief Updates the delta time (time elapsed) between frames.
             */
            void UpdateDeltaTime();

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
            /**
             * @brief Initializes SDL, window, and renderer.
             */
            void InitSDL();
            void InitSDLTTF();
            void InitSDLMixer();
            void InitSDLImage();
            void EventLoop();
    };
}