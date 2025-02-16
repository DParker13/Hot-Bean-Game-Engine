#include "input_system.hpp"

namespace Systems {
    InputSystem::InputSystem(Core::CoreManager& coreManager)
        : System(coreManager) {
        coreManager.RegisterSystem<InputSystem>(this);
        
        coreManager.SetSignature<InputSystem>(Signature{});
    }

    /**
     * @brief Handles an SDL event, adding/removing keys from the set of pressed keys
     * if the event is a key down or key up event.
     * @param[in] event The SDL event to handle.
     */
    void InputSystem::OnEvent(SDL_Event& event) {
        if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
            _keysPressed.insert(event.key.keysym.sym);
        }
        
        if (event.type == SDL_KEYUP) {
            _keysPressed.erase(event.key.keysym.sym);
        }
    }

    std::string InputSystem::ToString() const {
        return "  Input System Entities: " + std::to_string(_entities.size()) + "\n";
    }
}