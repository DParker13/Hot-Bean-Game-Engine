#include "game.hpp"

namespace Application {

    Game::~Game() = default;

    /**
     * Creates instances of the necessary systems
     * and game objects, such as the physics system, render system, input system,
     * player controller system, UI system, debug text, and player object.
     *
     * @throws None
     */
    void Game::InitLayer() {
        // System Manager handles destroying these items when they're unused
        new Systems::PhysicsSystem(_coreManager);
        new Systems::RenderSystem(_coreManager);
        new Systems::InputSystem(_coreManager);
        new Systems::PlayerControllerSystem(_coreManager);
        new Systems::UISystem(_coreManager);
        new Systems::TileMapSystem(_coreManager, 100, 100);
        auto audioSystem = new Systems::AudioSystem(_coreManager);

        audioSystem->LoadMusic("../assets/music/Summer.wav");
        audioSystem->PlayMusic(-1);
        
        InitMap(10, 1550, 800);

        auto debugText = GameObjects::Text(&_coreManager);
        auto playerObj = GameObjects::Player(&_coreManager);
    }

    void Game::EventLayer(SDL_Event event) {
        _coreManager.GetSystem<Systems::InputSystem>()->UpdateKeys(event);
    }

    void Game::UpdateLayer(float deltaTime) {
        auto keysPressed = _coreManager.GetSystem<Systems::InputSystem>()->_keysPressed;

        _coreManager.GetSystem<Systems::PlayerControllerSystem>()->Move(_coreManager, keysPressed, deltaTime, 100.0f);
        _coreManager.GetSystem<Systems::PhysicsSystem>()->Update(_coreManager, deltaTime);
        _coreManager.GetSystem<Systems::UISystem>()->Update(_coreManager);
    }

    void Game::RenderLayer(SDL_Renderer* renderer, SDL_Window* window, SDL_Surface* surface) {
        _coreManager.GetSystem<Systems::UISystem>()->Render(surface, renderer, _coreManager);
        _coreManager.GetSystem<Systems::TileMapSystem>()->RenderMap(surface, renderer, _coreManager);
    }

    // Should this be defined in TileMapSystem instead?
    void Game::InitMap(Uint32 tilePixelSize, Uint32 sizeX, Uint32 sizeY) {
    for (int x = 0; x < sizeX; x+=tilePixelSize*2) {
        for (int y = 0; y < sizeY; y+=tilePixelSize*2) {
            auto tile = GameObjects::Tile(&_coreManager);
            tile.GetTransform().position.x = x;
            tile.GetTransform().position.y = y;
        }
    }
}
}