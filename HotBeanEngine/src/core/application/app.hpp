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
#include <iostream>

#include "../managers/all_managers.hpp"

//using namespace Core::ECS;
using namespace Core::Managers;
using namespace Core::ECS;

namespace Core {
    namespace Application {

        /**
         * @brief Interface for all Application layers ordered in calling order
         */
        class App : public GameLoop {
            public:
                bool m_quit; ///< Flag to quit the application
    
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
                std::shared_ptr<ECSManager> GetECSManager() const;

                void Log(LoggingType type, std::string message);
                void SetLoggingLevel(LoggingType level);
                void SetLogPath(std::string log_path);
    
                /**
                 * @brief Entry point for the main loop of the application.
                 */
                void Run();

                // --- ECS Manager Extension --- //

                Entity CreateEntity();
                void DestroyEntity(Entity entity);

                template<typename T, typename... Args>
                T& RegisterSystem(Args&&... params) {
                    return m_ecs_manager->RegisterSystem<T, Args...>(std::forward<Args>(params)...);
                }

                template<typename T>
                T& RegisterSystem() {
                    return m_ecs_manager->RegisterSystem<T>();
                }

                template<typename T>
                void UnregisterSystem() {
                    m_ecs_manager->UnregisterSystem<T>();
                }
                
                template<typename T>
                void AddComponent(Entity entity, T component) {
                    m_ecs_manager->AddComponent<T>(entity, component);
                }

                template<typename T>
                T& GetComponent(Entity entity) {
                    return m_ecs_manager->GetComponent<T>(entity);
                }

                template<typename T>
                void RemoveComponent(Entity entity) {
                    m_ecs_manager->RemoveComponent<T>(entity);
                }
    
            protected:
                std::shared_ptr<ECSManager> m_ecs_manager;
                std::shared_ptr<LoggingManager> m_logging_manager;
                std::unique_ptr<SerializationManager> m_serialization_manager;
                SDL_Renderer* m_renderer;
                SDL_Window* m_window;
                SDL_Surface* m_surface;
                float m_delta_time; ///< Time elapsed between frames
                float m_previous_frame_time; ///< Previous frame time
                
                App(const std::string& config_path);

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
                 * @brief Initializes the application systems in the system manager.
                 */
                virtual void SetupSystems() = 0;
    
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
                static App* _instance; // singleton of the application
        };
    }
}