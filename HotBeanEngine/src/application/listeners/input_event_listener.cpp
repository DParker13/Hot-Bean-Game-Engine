/**
 * @file input_event_listener.cpp
 * @author Daniel Parker (DParker13)
 * @brief Implementation of the input event listener that handles SDL events.
 * Processes keyboard, mouse, and input state tracking.
 * @version 0.1
 * @date 2026-01-21
 *
 * @copyright Copyright (c) 2025
 */

#include <HotBeanEngine/application/listeners/input_event_listener.hpp>

namespace HBE::Application::Listeners {
    void InputEventListener::OnEvent(SDL_Event &event) {
        if (event.type == SDL_EVENT_KEY_DOWN && event.key.repeat == 0) {
            m_keys_pressed.insert(event.key.key);
            OnKeyDown(event);
        }
        else if (event.type == SDL_EVENT_KEY_UP) {
            m_keys_pressed.erase(event.key.key);
            OnKeyUp(event);
        }
        else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            m_mouse_buttons_pressed.insert(event.button.button);
            OnMouseButtonDown(event);
        }
        else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
            m_mouse_buttons_pressed.erase(event.button.button);
            OnMouseButtonUp(event);
        }
        else if (event.type == SDL_EVENT_MOUSE_MOTION) {
            m_mouse_position = {event.motion.x, event.motion.y};
            OnMouseMove(event);
        }
        else if (event.type == SDL_EVENT_MOUSE_WHEEL) {
            m_mouse_wheel_delta = event.wheel.y;
            OnMouseWheel(event);
        }
    }

    void InputEventListener::OnUpdate() {
        // Reset mouse wheel delta after processing
        m_mouse_wheel_delta = 0.0f;
    }
} // namespace HBE::Application::Listeners