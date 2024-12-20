#include "player_controller_system.hpp"

namespace Systems {
    PlayerControllerSystem::PlayerControllerSystem(Core::CoreManager& coreManager) {
        coreManager.RegisterSystem<Systems::PlayerControllerSystem>();

        coreManager.SetSignature<Systems::PlayerControllerSystem, Components::Transform>();
        coreManager.SetSignature<Systems::PlayerControllerSystem, Components::Player>();
    }

    void PlayerControllerSystem::Move(Core::CoreManager& coreManager, std::unordered_set<SDL_Keycode> keysPressed, float dt, float speed) {
        if (keysPressed.size() > 0) {
            float distance = speed * dt;

            for (auto& entity : _entities) {
                auto& player = coreManager.GetComponent<Components::Player>(entity);

                if (player.controllable) {
                    auto& transform = coreManager.GetComponent<Components::Transform>(entity);

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
    }

    std::string PlayerControllerSystem::ToString() const {
        return "  Player Controller System Entities: " + std::to_string(_entities.size()) + "\n";
    }
}