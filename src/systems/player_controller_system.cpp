#include "player_controller_system.hpp"

namespace Systems {
    PlayerControllerSystem::PlayerControllerSystem(Core::CoreManager& coreManager)
        : System(coreManager) {
        coreManager.RegisterSystem<PlayerControllerSystem>(this);

        coreManager.SetSignature<PlayerControllerSystem, Components::Transform2D>();
        coreManager.SetSignature<PlayerControllerSystem, Components::Controller>();
    }

    /**
     * Updates the state of all entities managed by the PlayerControllerSystem.
     * This function is called every frame and processes input to move entities.
     *
     * @param deltaTime The time elapsed since the last frame, used to ensure consistent movement speed.
     */
    void PlayerControllerSystem::OnUpdate(SDL_Renderer* renderer, float deltaTime) {
        auto keysPressed = _coreManager.GetSystem<Systems::InputSystem>()->_keysPressed;

        for (auto& entity : _entities) {
            Move(entity, keysPressed, deltaTime, 100);
        }
    }

    /**
     * Moves the given entity based on the given input keys and time elapsed since the last frame.
     *
     * @param entity The entity to move.
     * @param keysPressed The set of keys currently pressed.
     * @param deltaTime The time elapsed since the last frame.
     * @param speed The speed at which the entity will move, in pixels per second.
     */
    void PlayerControllerSystem::Move(Entity entity, std::unordered_set<SDL_Keycode> keysPressed, float deltaTime, float speed) {
        if (keysPressed.size() > 0) {
            float distance = speed * deltaTime;

            auto& controller = _coreManager.GetComponent<Components::Controller>(entity);

            if (controller.controllable) {
                auto& transform = _coreManager.GetComponent<Components::Transform2D>(entity);

                if (keysPressed.find(SDLK_LEFT) != keysPressed.end()) {
                    transform._position.x -= distance;
                }
                
                if (keysPressed.find(SDLK_RIGHT) != keysPressed.end()) {
                    transform._position.x += distance;
                }
                
                if (keysPressed.find(SDLK_UP) != keysPressed.end()) {
                    transform._position.y -= distance;
                }
                
                if (keysPressed.find(SDLK_DOWN) != keysPressed.end()) {
                    transform._position.y += distance;
                }
            }
        }
    }

    std::string PlayerControllerSystem::ToString() const {
        return "  Player Controller System Entities: " + std::to_string(_entities.size()) + "\n";
    }
}