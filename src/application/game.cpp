/**
 * @file game.cpp
 * @author Daniel Parker
 * @brief Game logic implementation.
 * Handles game state updates, user input processing, and rendering ontop of the Application class.
 * @version 0.1
 * @date 2025-02-18
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "game.hpp"

namespace Application {
    Game::~Game() {
        Application::~Application();
    }

    /**
     * @brief Initializes all systems in the game. This function creates an 
     * instance of each system that is used in the game.
     * 
     * @note The System Manager is responsible for cleaning up these
     * systems when they're no longer needed.
     */
    void Game::InitSystems() {
        new Systems::PhysicsSystem(_coreManager);
        new Systems::RenderSystem(_coreManager);
        new Systems::InputSystem(_coreManager);
        new Systems::PlayerControllerSystem(_coreManager);
        new Systems::UISystem(_coreManager);
        new Systems::TileMapSystem(_coreManager);
        new Systems::AudioSystem(_coreManager);
    }

    /**
     * @brief Initializes gameobjects and sets up their starting state.
     */
    void Game::OnInit() {
        Application::OnInit();

        auto fpsText = GameObjects::UI::Text(&_coreManager);
        auto testText = GameObjects::UI::Text(&_coreManager);

        fpsText.GetTexture()._size = { 1000.0f, 100.0f };
        fpsText.GetText()._size = 50;
        fpsText.GetText().SetText("Layer 0!");

        testText.GetTransform2D()._position = { 500.0f, 50.0f };
        testText.GetTransform2D()._layer = 1;
        testText.GetTexture()._size = { 1000.0f, 100.0f };
        testText.GetText()._size = 50;
        testText.GetText().SetText("Layer 1!");
        _coreManager.AddComponent<Components::Controller>(fpsText.GetEntity(), Components::Controller());
    }

    /**
     * @brief Calls the OnEvent method of all systems and each system
     * will handle their SDL events.
     *
     * @param event The SDL event to handle.
     */
    void Game::OnEvent(SDL_Event& event) {
        Application::OnEvent(event);
    }

    /**
     * @brief Calls the OnUpdate method of all systems and each system
     * will update their entities.
     * 
     * @param deltaTime The time in seconds since the last frame.
     */
    void Game::OnUpdate(SDL_Renderer* renderer, float deltaTime) {
        Application::OnUpdate(renderer, deltaTime);
    }

    /**
     * @brief Calls the OnRender method of all systems and each system
     * will render their entities and resources to the screen.
     *
     * @param renderer The renderer to use to render the game.
     * @param window The window to render to.
     * @param surface The surface to render to.
     */
    void Game::OnRender(SDL_Renderer* renderer, SDL_Window* window, SDL_Surface* surface) {
        Application::OnRender(renderer, window, surface);
    }

    /**
     * @brief Calls the OnPostRender method of all systems.
     *
     * @param renderer The renderer to use to render the game.
     */
    void Game::OnPostRender(SDL_Renderer* renderer) {
        Application::OnPostRender(renderer);
    }
}