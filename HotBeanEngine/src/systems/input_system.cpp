#include "input_system.hpp"

namespace Systems {
    void InputSystem::SetSignature() {
        SETUP_SYSTEM(InputSystem);
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
}