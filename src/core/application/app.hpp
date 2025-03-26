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

#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <vector>
#include <memory>
#include <iostream>

#include "../managers/core_manager.hpp"

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
                CoreManager _coreManager;
                bool _quit; ///< Flag to quit the application
    
                App(std::string title, int width, int height);
                ~App();

                // Getters and Setters
                CoreManager& GetCoreManager();
                SDL_Renderer* GetRenderer() const;
                void SetRenderer(SDL_Renderer* renderer);
                SDL_Window* GetWindow() const;
                void SetWindow(SDL_Window* window);
                SDL_Surface* GetSurface() const;
                void SetSurface(SDL_Surface* surface);
                float GetDeltaTime() const;
    
                /**
                 * @brief Entry point for the main loop of the application.
                 */
                void Run();
    
            protected:
                SDL_Renderer* _renderer;
                SDL_Window* _window;
                SDL_Surface* _surface;
                float _deltaTime; ///< Time elapsed between frames
                float _previousFrameTime; ///< Previous frame time
    
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
                virtual void InitSystems() = 0;
    
                /**
                 * @brief Called once at the start of the game.
                 */
                virtual void OnInit() = 0;
    
                /**
                 * @brief Called before handling events.
                 */
                virtual void OnPreEvent() = 0;
    
                /**
                 * @brief Called when an event occurs.
                 * 
                 * @param event The SDL event to handle.
                 */
                virtual void OnEvent(SDL_Event& event) = 0;
    
                /**
                 * @brief Called after handling events. Meant to update system and entity game states.
                 */
                virtual void OnUpdate() = 0;
    
                /**
                 * @brief Called to prepare the screen for rendering.
                 */
                virtual void OnRender() = 0;
    
                /**
                 * @brief Called after rendering each frame.
                 */
                virtual void OnPostRender() = 0;

                void LoadScene(std::shared_ptr<Scene> scene) {
                    
                }
        };
    }
}