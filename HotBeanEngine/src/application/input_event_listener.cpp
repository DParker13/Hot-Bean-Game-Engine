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

#include <HotBeanEngine/application/input_event_listener.hpp>

namespace HBE::Application {
    void InputEventListener::OnEvent(SDL_Event &event) {
        if (event.type == SDL_EVENT_KEY_DOWN && event.key.repeat == 0) {
            m_keys_pressed.insert(event.key.key);
            OnKeyDown(event);
            LOG_CORE(HBE::Core::LoggingType::DEBUG, "Key Down: " + std::to_string(event.key.key));
        }
        else if (event.type == SDL_EVENT_KEY_UP) {
            m_keys_pressed.erase(event.key.key);
            OnKeyUp(event);
            LOG_CORE(HBE::Core::LoggingType::DEBUG, "Key Up: " + std::to_string(event.key.key));
        }
        else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            m_mouse_buttons_pressed.insert(event.button.button);
            OnMouseButtonDown(event);
            LOG_CORE(HBE::Core::LoggingType::DEBUG, "Mouse Button Down: " + std::to_string(event.button.button));
        }
        else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
            m_mouse_buttons_pressed.erase(event.button.button);
            OnMouseButtonUp(event);
            LOG_CORE(HBE::Core::LoggingType::DEBUG, "Mouse Button Up: " + std::to_string(event.button.button));
        }
        else if (event.type == SDL_EVENT_MOUSE_MOTION) {
            m_mouse_position = {event.motion.x, event.motion.y};
            OnMouseMove(event);
            LOG_CORE(HBE::Core::LoggingType::DEBUG,
                     "Mouse Move: (" + std::to_string(event.motion.x) + ", " + std::to_string(event.motion.y) + ")");
        }
    }
} // namespace HBE::Application