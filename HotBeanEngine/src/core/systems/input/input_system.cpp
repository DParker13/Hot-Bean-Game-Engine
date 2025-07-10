#include "input_system.hpp"

namespace Core::Systems {
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
            m_keys_pressed.insert(event.key.keysym.sym);
        }
        
        if (event.type == SDL_KEYUP) {
            m_keys_pressed.erase(event.key.keysym.sym);
        }
    }
}