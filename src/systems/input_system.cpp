#include "input_system.hpp"

namespace Systems {
    void InputSystem::HandleEvent(Core::CoreManager& coreManager, SDL_Event& event, float dt) {
        float distance = speed * dt;

        if (UpdateInput(event)) {
            for (auto& entity : _entities) {
                auto& transform = coreManager.GetComponent<Components::Transform>(entity);

                if (_keysPressed.find(SDLK_LEFT) != _keysPressed.end() && _keysPressed[SDLK_LEFT] == true) {
                    transform.position.x -= distance;
                }
                
                if (_keysPressed.find(SDLK_RIGHT) != _keysPressed.end() && _keysPressed[SDLK_RIGHT] == true) {
                    transform.position.x += distance;
                }
                
                if (_keysPressed.find(SDLK_UP) != _keysPressed.end() && _keysPressed[SDLK_UP] == true) {
                    transform.position.y -= distance;
                }
                
                if (_keysPressed.find(SDLK_DOWN) != _keysPressed.end() && _keysPressed[SDLK_DOWN] == true) {
                    transform.position.y += distance;
                }
            }
        }
    }

    bool InputSystem::UpdateInput(SDL_Event& event) {
        if (event.type == SDL_KEYDOWN) {
            if (_keysPressed.find(event.key.keysym.sym) != _keysPressed.end()) {
                _keysPressed.insert({event.key.keysym.sym, true});
                return true;
            }
        }
        else if (event.type == SDL_KEYUP) {
            if (_keysPressed.find(event.key.keysym.sym) != _keysPressed.end()) {
                _keysPressed.erase(event.key.keysym.sym);
                return true;
            }
        }

        return false;
    }

    void InputSystem::Print() const {
        std::cout << "  Input System Entities: " << _entities.size() << std::endl;
    }
}