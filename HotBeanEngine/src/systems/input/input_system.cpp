#include "input_system.hpp"

namespace Systems {
    /**
     * @brief Handles an SDL event, adding/removing keys from the set of pressed keys
     * if the event is a key down or key up event.
     * @param[in] event The SDL event to handle.
     */
    void InputSystem::OnEvent(SDL_Event& event) {
        if (event.type == SDL_KEYDOWN) {
            OnKeyDown(event);
        }
        else if (event.type == SDL_KEYUP) {
            OnKeyUp(event);
        }
        else if(event.type == SDL_MOUSEBUTTONDOWN) {
            OnMouseButtonDown(event);
        }
        else if (event.type == SDL_MOUSEBUTTONUP) {
            OnMouseButtonUp(event);
        }
        else if (event.type == SDL_MOUSEMOTION) {
            OnMouseMove(event);
        }
    }

    void InputSystem::OnKeyDown(SDL_Event& event) {
        if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
            m_keys_pressed.insert(event.key.keysym.sym);
        }
    }

    void InputSystem::OnKeyUp(SDL_Event& event) {
        if (event.type == SDL_KEYUP) {
            m_keys_pressed.erase(event.key.keysym.sym);
        }
    }

    void InputSystem::OnMouseButtonDown(SDL_Event& event) {
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            m_mouse_buttons_pressed.insert(event.button.button);
        }
    }

    void InputSystem::OnMouseButtonUp(SDL_Event& event) {
        if (event.type == SDL_MOUSEBUTTONUP) {
            m_mouse_buttons_pressed.erase(event.button.button);
        }
    }

    void InputSystem::OnMouseMove(SDL_Event& event) {
        if (event.type == SDL_MOUSEMOTION) {
            m_mouse_position = {event.motion.x, event.motion.y};
        }
    }
}