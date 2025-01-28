#include "game.hpp"

namespace Application {

    Game::~Game() = default;

    /**
     * Initializes all systems in the game.
     *
     * This function creates an instance of each system that is used in the game.
     * The System Manager is responsible for cleaning up these systems when they're
     * no longer needed.
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
     * Initializes the game with some objects.
     *
     * This function is called after all systems have been initialized.
     */
    void Game::OnInit() {
        Application::OnInit();

        auto debugText = GameObjects::Text(&_coreManager);
        auto playerObj = GameObjects::Player(&_coreManager);
    }

    /**
     * Handles SDL events for the game.
     *
     * @param event The SDL event to handle.
     *
     * @throws None
     */
    void Game::OnEvent(SDL_Event& event) {
        Application::OnEvent(event);
    }

    /**
     * Updates the game state.
     *
     * This function calls the Application::OnUpdate() function to update the
     * state of all systems in the game. The deltaTime parameter is the time in
     * seconds since the last frame.
     *
     * @param deltaTime The time in seconds since the last frame.
     *
     * @throws None
     */
    void Game::OnUpdate(float deltaTime) {
        Application::OnUpdate(deltaTime);
    }

    /**
     * Renders the game state to the screen.
     *
     * This function calls the Application::OnRender() function to render the
     * state of all systems in the game. This is where the game is drawn to the
     * screen.
     *
     * @param renderer The renderer to use to render the game.
     * @param window The window to render to.
     * @param surface The surface to render to.
     *
     * @throws None
     */
    void Game::OnRender(SDL_Renderer* renderer, SDL_Window* window, SDL_Surface* surface) {
        Application::OnRender(renderer, window, surface);
    }
}