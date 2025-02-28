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

#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <vector>
#include <memory>
#include <iostream>

#include "../core/managers/core_manager.hpp"

namespace Application {

    /**
     * @brief Interface for all Application layers ordered in calling order
     */
    class Application : public IGameLoop {
        private:
            SDL_Window* _window;
            SDL_Renderer* _renderer;
            SDL_Surface* _surface;
            float _deltaTime; ///< Time elapsed between frames
            float _previousFrameTime; ///< Previous frame time

            /**
             * @brief Initializes the SDL window and renderer.
             * 
             * @param title Title of the application window.
             * @param width Width of the application window.
             * @param height Height of the application window.
             */
            void InitApplication(std::string title, int width, int height);

            /**
             * @brief Cleans up the SDL window and renderer.
             */
            void CleanUpSDL();

            /**
             * @brief Updates the delta time (time elapsed) between frames.
             */
            void UpdateDeltaTime();

        public:
            Core::CoreManager _coreManager;
            bool _quit; ///< Flag to quit the application

            Application(std::string title, int width, int height);
            ~Application();

            /**
             * @brief Entry point for the main loop of the application.
             */
            void Run();

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
             * 
             * @param renderer The SDL renderer used to render each frame.
             * @param deltaTime The time in seconds since the last frame.
             */
            virtual void OnUpdate(SDL_Renderer* renderer, float deltaTime) = 0;

            /**
             * @brief Called to prepare the screen for rendering.
             * 
             * @param renderer The SDL renderer used to render each frame.
             * @param window The SDL window used to render each frame.
             * @param surface The SDL surface used to render each frame.
             */
            virtual void OnRender(SDL_Renderer* renderer, SDL_Window* window, SDL_Surface* surface) = 0;

            /**
             * @brief Called after rendering each frame.
             * @param renderer The SDL renderer used to render each frame.
             */
            virtual void OnPostRender(SDL_Renderer* renderer) = 0;
    };
}