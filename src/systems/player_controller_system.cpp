#include "player_controller_system.hpp"

namespace Systems {
    PlayerControllerSystem::PlayerControllerSystem(Core::CoreManager& coreManager)
        : System(coreManager) {
        coreManager.RegisterSystem<PlayerControllerSystem>(this);

        coreManager.SetSignature<PlayerControllerSystem, Components::Transform>();
        coreManager.SetSignature<PlayerControllerSystem, Components::Player>();
    }

    void PlayerControllerSystem::OnUpdate(float deltaTime) {
        auto keysPressed = _coreManager.GetSystem<Systems::InputSystem>()->_keysPressed;

        for (auto& entity : _entities) {
            Move(entity, keysPressed, deltaTime, 100);
        }
    }

    void PlayerControllerSystem::Move(Entity entity, std::unordered_set<SDL_Keycode> keysPressed, float deltaTime, float speed) {
        if (keysPressed.size() > 0) {
            float distance = speed * deltaTime;

            auto& player = _coreManager.GetComponent<Components::Player>(entity);

            if (player.controllable) {
                auto& transform = _coreManager.GetComponent<Components::Transform>(entity);

                if (keysPressed.find(SDLK_LEFT) != keysPressed.end()) {
                    transform.position.x -= distance;
                }
                
                if (keysPressed.find(SDLK_RIGHT) != keysPressed.end()) {
                    transform.position.x += distance;
                }
                
                if (keysPressed.find(SDLK_UP) != keysPressed.end()) {
                    transform.position.y -= distance;
                }
                
                if (keysPressed.find(SDLK_DOWN) != keysPressed.end()) {
                    transform.position.y += distance;
                }
            }
        }
    }

    std::string PlayerControllerSystem::ToString() const {
        return "  Player Controller System Entities: " + std::to_string(_entities.size()) + "\n";
    }
}