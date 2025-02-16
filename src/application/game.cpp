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
     * @brief Called before the main game loop starts. Used to initialize objects.
     * 
     */
    void Game::OnInit() {
        Application::OnInit();

        auto fpsText = GameObjects::Text(&_coreManager);
        auto testText = GameObjects::Text(&_coreManager);
        auto playerObj = GameObjects::Player(&_coreManager);

        testText.GetTransform().position = { 500.0f, 500.0f, 0.0f };
        testText.GetTexture()._size = { 1000.0f, 100.0f };
        testText.GetText()._size = 50;
        testText.GetText().SetText("Hello World!");
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