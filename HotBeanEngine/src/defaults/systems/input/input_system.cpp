/**
 * @file input_system.cpp
 * @author Daniel Parker
 * @brief System for handling keyboard and mouse input events.
 * @version 0.1
 * @date 2024-12-20
 * 
 * @copyright Copyright (c) 2024
 */

#include <HotBeanEngine/defaults/systems/input/input_system.hpp>

namespace HBE::Default::Systems {
    /**
     * @brief Handles an SDL event, adding/removing keys from the set of pressed keys
     * if the event is a key down or key up event.
     * @param[in] event The SDL event to handle.
     */
    void InputSystem::OnEvent(SDL_Event& event) {
        if (event.type == SDL_EVENT_KEY_DOWN) {
            OnKeyDown(event);
        }
        else if (event.type == SDL_EVENT_KEY_UP) {
            OnKeyUp(event);
        }
        else if(event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            OnMouseButtonDown(event);
        }
        else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
            OnMouseButtonUp(event);
        }
        else if (event.type == SDL_EVENT_MOUSE_MOTION) {
            OnMouseMove(event);
        }
    }

    void InputSystem::OnKeyDown(SDL_Event& event) {
        if (event.type == SDL_EVENT_KEY_DOWN && event.key.repeat == 0) {
            m_keys_pressed.insert(event.key.key);
        }
    }

    void InputSystem::OnKeyUp(SDL_Event& event) {
        if (event.type == SDL_EVENT_KEY_UP) {
            m_keys_pressed.erase(event.key.key);
        }
    }

    void InputSystem::OnMouseButtonDown(SDL_Event& event) {
        if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            m_mouse_buttons_pressed.insert(event.button.button);
        }
    }

    void InputSystem::OnMouseButtonUp(SDL_Event& event) {
        if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
            m_mouse_buttons_pressed.erase(event.button.button);
        }
    }

    void InputSystem::OnMouseMove(SDL_Event& event) {
        if (event.type == SDL_EVENT_MOUSE_MOTION) {
            m_mouse_position = {event.motion.x, event.motion.y};
        }
    }
}